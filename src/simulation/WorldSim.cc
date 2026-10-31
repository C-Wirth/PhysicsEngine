#include <vector>
#include <ostream>
#include <sstream>
#include <array>
#include <stdexcept>

#include <toml++/toml.hpp>

#include "simulation/WorldSim.hh"
#include "physics/2D/KinematicState2D.hh"
#include "physics/2D/AbstractElement2D.hh"
#include "physics/2D/Particle2D.hh"

/**
 * Constructor: parses the toml file and instantiates the Elements
 */
WorldSim::WorldSim()
    : config_(toml::parse_file(CONFIG_PATH))
{
    const auto* simulation = config_[SIMULATION_HEADER].as_table();
    if (!simulation)
        throw std::runtime_error("Simulation entry must be a table");
    step_rate_hz = (*simulation)["step_rate_hz"].value<double>().value();


    const auto* particle2d_table = config_[PARTICLE2D_HEADER].as_table();
    if (!particle2d_table)
        throw std::runtime_error("Particle2D entry must be a table");

    particle2d_table->for_each([this](const std::string_view name, const toml::node& node)
    {
        const auto* particle = node.as_table();
        if (!particle)
            throw std::runtime_error("Particle entry must be a table");

        const auto parse_vector = [particle](const std::string_view key)
        {
            const auto* values = (*particle)[key].as_array();
            if (!values || values->size() != 2)
                throw std::runtime_error("Particle vector must contain exactly two numbers");

            std::array<double, 2> components{};
            for (std::size_t i = 0; i < components.size(); ++i)
                components[i] = (*values)[i].value<double>().value();

            return VectorM{components};
        };

        const auto acceleration = parse_vector(ACCELERATION_2D_VECTOR);
        const auto velocity = parse_vector(VELOCITY_2D_VECTOR);
        const auto position = parse_vector(POSITION_2D_VECTOR);

        KinematicState2D state{.acceleration = acceleration, .velocity = velocity, .position = position};

        elements_2d.emplace_back(std::make_unique<Particle2D>(state, std::string{name}));
    });
};


/**
 * steps the simulator foward at step_rate
 *
 */
auto WorldSim::stepSimulation() -> void
{
    return;
    // 1. determine forces O(E * F) where E=Elements and F=Forces

    // 2. accumulate forces

    // 3. calculate acceleration

    // 4. run numerical integrator

    // 5. update state

    // 6. continue
};

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
