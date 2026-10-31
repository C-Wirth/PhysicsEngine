#pragma once

#include <ostream>
#include <string>
#include <vector>


#include <toml++/toml.hpp>

#include "physics/2D/AbstractElement2D.hh"

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
    std::vector<std::unique_ptr<AbstractElement2D>> elements_2d;



    /**
     * Default constructor parses the toml config file and populates each entry in the simulator
     */
    WorldSim();

    /**
     * core logic for a step in the simulation
     */
    auto stepSimulation() -> void;

    /**
     * override the << operator to print the config
     * @return
     */
    friend auto operator<<(std::ostream&, const WorldSim&) -> std::ostream&;

private:
    toml::table config_;
};
