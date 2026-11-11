#include <utility>
#include <vector>
#include <ostream>
#include <sstream>
#include <array>
#include <cstddef>
#include <stdexcept>

#include <toml++/toml.hpp>

#include "simulation/WorldSim.hh"

#include <ranges>

#include "math/Integrator.hh"
#include "physics/2D/KinematicState2D.hh"
#include "physics/2D/AbstractElement2D.hh"
#include "physics/2D/Particle2D.hh"

/**
 * Constructor: parses the toml file and instantiates all
 * Elements, AppliedForces,
 */
WorldSim::WorldSim()
    : config_(toml::parse_file(CONFIG_PATH))
{
    parse_config_table();
}

/**
 * Constructor that takes a toml config table as a parameter
 * @param config_table
 */
WorldSim::WorldSim(toml::v3::table config_table)
    : config_(std::move(config_table))
{
    parse_config_table();
}


auto WorldSim::parse_config_table() -> void
{
    // simulation settings
    const auto* simulation = config_[SIMULATION_HEADER].as_table();
    if (!simulation)
        throw std::runtime_error("Simulation entry must be a table");

    const auto integrator_name = (*simulation)["integrator"].value<std::string>();
    if (!integrator_name)
        throw std::runtime_error("Simulation integrator not recognized");
    Integrator::getInstance().setIntegrator(*integrator_name);

    const double step_rate_hz = (*simulation)["step_rate_hz"].value<double>().value();
    if (step_rate_hz <= 0.0)
        throw std::runtime_error("Simulation step_rate_hz must be greater than zero");
    time_step_s = 1.0 / step_rate_hz;


    // particle2Ds
    const auto* particle2d_table = config_[PARTICLE_2D_HEADER].as_table();
    if (!particle2d_table)
        throw std::runtime_error("Particle2D entry must be a table");

    particle2d_table->for_each([this](const std::string_view name, const toml::node& node)
    {
        const auto* particle = node.as_table();
        if (!particle)
            throw std::runtime_error("Particle2D entry must be a table");

        const auto parse_vector = [particle](const std::string& key)
        {
            const auto* values = (*particle)[key].as_array();
            if (!values || values->size() != 2)
                throw std::runtime_error("Particle2D vector must contain exactly two numbers");

            std::array<double, 2> components{};
            for (std::size_t i = 0; i < components.size(); ++i)
                components[i] = (*values)[i].value<double>().value();

            return VectorM{components};
        };

        const auto acceleration = parse_vector(ACCELERATION_2D_VECTOR);
        const auto velocity = parse_vector(VELOCITY_2D_VECTOR);
        const auto position = parse_vector(POSITION_2D_VECTOR);

        KinematicState2D state{.acceleration = acceleration, .velocity = velocity, .position = position};

        const auto mass = (*particle)[MASS_VALUE].value<double>();
        if (!mass)
            throw std::runtime_error("Particle2D mass must be a number");


        auto element_name = std::string{name};
        elements_2d.emplace(element_name, std::make_unique<Particle2D>(element_name, state, *mass));
    });

    // applied forces
    const auto* applied_force_table = config_[APPLIED_FORCE_2D_HEADER].as_table();
    if (!applied_force_table)
        throw std::runtime_error("AppliedForce must be a table");

    applied_force_table->for_each([this](const std::string_view name, const toml::node& node)
    {
        const auto* applied_force_table = node.as_table();
        if (!applied_force_table)
            throw std::runtime_error("AppliedForce entry must be a table");

        const auto* force_values = (*applied_force_table)[APPLIED_FORCE_2D_FORCE].as_array();
        const auto* target_particles = (*applied_force_table)[APPLIED_FORCE_2D_TARGET_PARTICLES].as_array();
        const auto* time_config = (*applied_force_table)[APPLIED_FORCE_2D_START_AND_DURATION_PAIRS].as_array();

        if (!force_values || force_values->size() != 2)
            throw std::runtime_error("AppliedForce2D force must contain exactly two numbers");
        if (!target_particles)
            throw std::runtime_error("AppliedForce2D target_particles must be an array");
        if (!time_config)
            throw std::runtime_error("AppliedForce2D start_and_duration_pairs must be an array");

        std::array<double, 2> force_components{};
        for (std::size_t i = 0; i < force_components.size(); ++i)
            force_components[i] = (*force_values)[i].value<double>().value();
        const VectorM<2> force_vector{force_components};

        for (const auto& particle_node : *target_particles)
        {
            const auto particle_name = particle_node.value<std::string>();
            if (!particle_name)
                throw std::runtime_error("AppliedForce2D target particle names must be strings");

            for (const auto& pair_node : *time_config)
            {
                const auto* pair = pair_node.as_array();
                if (!pair || pair->size() != 2)
                    throw std::runtime_error("Each start_and_duration_pairs entry must contain start and duration");

                const double timestamp = (*pair)[0].value<double>().value();
                const double duration = (*pair)[1].value<double>().value();
                appliedForceSchedule.emplace_back(ScheduledForce{
                    .timestamp = timestamp,
                    .duration = duration,
                    .target_element_name = *particle_name,
                    .force = AppliedForce2D{force_vector}
                });
            }
        }
    });
}

/**
 * used once every WorldSim::step() to determine all active forces
 */
auto WorldSim::determine_forces() -> void
{
    //  ensure that the determined_forces vector is empty
    determined_forces.clear();

    std::size_t idx = 0;

    // this logic steps through the schedule of predefined applied forces
    while (idx < appliedForceSchedule.size())
    {
        // ReSharper disable once CppUseStructuredBinding
        auto& scheduled_force = appliedForceSchedule[idx];

        // we have not yet reached the time to
        if (current_time_s < scheduled_force.timestamp)
        {
            ++idx;
            continue;
        }

        const bool is_instant_force = scheduled_force.duration == 0.0;

        const bool duration_has_ended =
            !is_instant_force && current_time_s >= scheduled_force.timestamp + scheduled_force.duration;

        if (duration_has_ended)
        {
            appliedForceSchedule.erase(appliedForceSchedule.begin() + static_cast<std::ptrdiff_t>(idx));
            continue;
        }

        const auto target_element = elements_2d.find(scheduled_force.target_element_name);
        if (target_element != elements_2d.end() && target_element->second)
        {
            determined_forces.push_back(DeterminedForce{
                .target_element_name = scheduled_force.target_element_name,
                .force = std::make_unique<AppliedForce2D>(scheduled_force.force)
            });
        }

        if (is_instant_force)
        {
            appliedForceSchedule.erase(appliedForceSchedule.begin() + static_cast<std::ptrdiff_t>(idx));
            continue;
        }

        ++idx;
    }

    // TODO apply non-scheduled Forces
}


auto WorldSim::accumulate_forces() -> void
{
    for (auto& determined_force : determined_forces)
    {
        const auto target_element = elements_2d.find(determined_force.target_element_name);
        if (target_element == elements_2d.end() ||
            !target_element->second ||
            !determined_force.force
        )
        {
            continue;
        }

        determined_force.force->applyForce(*target_element->second);
    }
}


auto WorldSim::calculate_acceleration() -> void
{
    for (const auto& element : elements_2d | std::views::values)
    {
        element->set_acceleration(element->getAccumulatedForces() / element->get_mass());
    }
}


auto WorldSim::integrate() -> void
{

    for (const auto& e : elements_2d | std::views::values)
    {
        Integrator::getInstance().stepIntegrator(e->get_kinematic_state(), time_step_s);
    }
}


auto WorldSim::reset_accumulators() -> void
{
    for (const auto& e : elements_2d | std::views::values)
    {
        e->resetAccumulatedForces();
    }

}

/**
 * steps the simulator forward at step_rate
 * 1. determine forces
 * 2. accumulate forces
 * 3. calculate acceleration
 * 4. integrate
 * 5. update state and reset accumulators
 *
 */
auto WorldSim::stepSimulation() -> void
{
    determine_forces();
    accumulate_forces();
    calculate_acceleration();
    integrate();
    reset_accumulators();
    current_time_s += time_step_s;

}

/**
 * operator<< overload for printing a config.
 * @param os the stream
 * @param world_sim the WorldSim object
 * @return
 */
auto operator<<(std::ostream& os, const WorldSim& world_sim) -> std::ostream&
{
    os << "WorldSim Config:\n";

    std::stringstream ss;

    ss << toml::toml_formatter{world_sim.config_};

    std::string line;
    while (std::getline(ss, line))
    {
        os << "\t" << line << "\n";
    }
    return os;
}
