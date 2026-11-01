#pragma once

#include <ostream>
#include <memory>
#include <string>
#include <vector>


#include <toml++/toml.hpp>

#include "physics/2D/AbstractElement2D.hh"
#include "physics/2D/Forces/AppliedForce2D.hh"

inline std::string CONFIG_PATH = "config.toml";

inline std::string SIMULATION_HEADER = "Simulation";
inline std::string STEP_RATE_HZ = "step_rate_hz";

inline std::string PARTICLE_2D_HEADER = "Particle2D";
inline std::string ACCELERATION_2D_VECTOR = "acceleration";
inline std::string VELOCITY_2D_VECTOR = "velocity";
inline std::string POSITION_2D_VECTOR = "position";


inline std::string APPLIED_FORCE_2D_HEADER = "AppliedForce2D";
inline std::string APPLIED_FORCE_2D_FORCE = "force";
inline std::string APPLIED_FORCE_2D_TARGET_PARTICLES = "target_particles";
inline std::string APPLIED_FORCE_2D_START_AND_DURATION_PAIRS = "start_and_duration_pairs";


class WorldSim
{
public:
    /**
     * The an entry in the Element lookup table
     */
    struct ElementEntry
    {
        std::string name;
        std::unique_ptr<AbstractElement2D> element2_d;
    };


    /**
     * The Force entry in the Force Schedule
     */
    struct ScheduledForce
    {
        double timestamp;
        double duration;
        std::string target_element_name;
        AppliedForce2D force;
    };


    double step_rate_hz{};
    std::vector<std::unique_ptr<ElementEntry>> elements_2d;
    std::vector<ScheduledForce> appliedForceSchedule{};


    /**
     * Default constructor parses the toml config file and populates each entry in the simulator
     */
    WorldSim();

    /**
     * Constructor that takes a toml table.  Currently used for testing
     */
    WorldSim(toml::v3::table);

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
    /**
     * helper function to parse a config file
     */
    auto parse_config_table() -> void;

    toml::table config_;
};
