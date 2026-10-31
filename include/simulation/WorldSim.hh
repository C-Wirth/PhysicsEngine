#pragma once

#include <ostream>
#include <sstream>
#include <array>
#include <stdexcept>
#include <string>
#include <vector>


#include <toml++/toml.hpp>

#include "math/VectorM.hh"
#include "physics/KinematicState2D.hh"
#include "physics/Particle2D.hh"


inline std::string CONFIG_PATH = "config.toml";
inline std::string SIMULATION_HEADER = "Simulation";
inline std::string STEP_RATE_HZ = "step_rate_hz";
inline std::string PARTICLE2D_HEADER = "Particle2D";
inline std::string ACCELERATION_2D_VECTOR = "acceleration";
inline std::string VELOCITY_2D_VECTOR = "velocity";
inline std::string POSITION_2D_VECTOR = "position";

class WorldSim
{
public:
    double step_rate_hz{};
    std::vector<Particle2D> particles2d{};


    /**
     * Default constructor
     */
    explicit WorldSim()
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
            particles2d.emplace_back(state, std::string{name});
        });
    }


    /**
     * operator<< overload for printing a config.
     * @param os the stream
     * @param world_sim the WorldSim object
     * @return
     */
    friend auto operator<<(std::ostream& os, const WorldSim& world_sim) -> std::ostream&
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

private:
    toml::table config_;
};
