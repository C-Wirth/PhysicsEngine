#include <cassert>
#include <utility>

#include <toml++/toml.hpp>

#include "simulation/WorldSim.hh"

class WorldSimTestAccess
{
public:
    static auto SetCurrentTime(WorldSim& sim, const double time_s, const bool step_simulation) -> void
    {
        sim.current_time_s = time_s;
        if (step_simulation)
            sim.stepSimulation();
    }

    static auto determine_forces(WorldSim& sim) -> void
    {
        sim.determine_forces();
    }
};

static auto test_parse_config_table() -> void
{
    toml::table config_table{
        {
            "Simulation", toml::table{
                {"step_rate_hz", 60.0},
                {"integrator", "Euler"}
            }
        },
        {
            "Particle2D", toml::table{
                {
                    "particle1", toml::table{
                        {"acceleration", toml::array{0.0, 0.0}},
                        {"velocity", toml::array{-1.0, -1.0}},
                        {"position", toml::array{0.0, 0.0}},
                        {"mass", 1.0},
                    }
                },
                {
                    "particle2", toml::table{
                        {"acceleration", toml::array{0.0, 0.0}},
                        {"velocity", toml::array{1.0, 1.0}},
                        {"position", toml::array{1.0, 1.0}},
                        {"mass", 2.0},
                    }
                }
            }
        },
        {
            "AppliedForce2D", toml::table{
                {
                    "force1", toml::table{
                        {"force", toml::array{1.0, 1.0}},
                        {"target_particles", toml::array{"particle1"}},
                        {
                            "start_and_duration_pairs", toml::array{
                                toml::array{0.0, 0.0},
                                toml::array{5.0, 0.0}
                            }
                        }
                    }
                }
            }
        }
    };

    const WorldSim sim{std::move(config_table)};

    assert(sim.getTimeStepS() == 1.0 / 60.0);
    assert(sim.elements_2d.size() == 2);
    assert(sim.appliedForceSchedule.size() == 2);
    assert(sim.appliedForceSchedule[0].target_element_name == "particle1");
    assert(sim.appliedForceSchedule[0].timestamp == 0.0);
    assert(sim.appliedForceSchedule[1].timestamp == 5.0);
}


static auto test_determine_forces() -> void
{
    {
        toml::table config_table{
            {
                "Simulation", toml::table{
                    {"step_rate_hz", 60.0},
                    {"integrator", "Euler"}
                }
            },
            {
                "Particle2D", toml::table{
                    {
                        "particle1", toml::table{
                            {"acceleration", toml::array{0.0, 0.0}},
                            {"velocity", toml::array{-1.0, -1.0}},
                            {"position", toml::array{0.0, 0.0}},
                            {"mass", 2.0},
                        }
                    }
                }
            },
            {
                "AppliedForce2D", toml::table{
                    {
                        "force1", toml::table{
                            {"force", toml::array{1.0, 1.0}},
                            {"target_particles", toml::array{"particle1"}},
                            {
                                "start_and_duration_pairs", toml::array{
                                    toml::array{0.0, 0.0},
                                    toml::array{0.0, 1.0}
                                }
                            }
                        }
                    },
                }
            }
        };

        WorldSim sim{std::move(config_table)};

        assert(sim.appliedForceSchedule.size() == 2);

        // At t = 0, both scheduled forces are determined.
        WorldSimTestAccess::SetCurrentTime(sim, 0.0, false);
        WorldSimTestAccess::determine_forces(sim);
        assert(sim.determined_forces.size() == 2);
        assert(sim.determined_forces[0].target_element_name == "particle1");
        assert(sim.determined_forces[0].force);
        assert(sim.determined_forces[1].target_element_name == "particle1");
        assert(sim.determined_forces[1].force);
        assert(sim.appliedForceSchedule.size() == 1);
        assert(sim.appliedForceSchedule[0].timestamp == 0.0);

        // At t = 0.5, the duration force remains active.
        WorldSimTestAccess::SetCurrentTime(sim, 0.5, false);
        WorldSimTestAccess::determine_forces(sim);
        assert(sim.determined_forces.size() == 1);
        assert(sim.determined_forces[0].target_element_name == "particle1");
        assert(sim.appliedForceSchedule.size() == 1);

        // At t = 1, the duration force has ended and is removed.
        WorldSimTestAccess::SetCurrentTime(sim, 1.0, false);
        WorldSimTestAccess::determine_forces(sim);
        assert(sim.determined_forces.empty());
        assert(sim.appliedForceSchedule.empty());
    }
}

int main()
{
    test_parse_config_table();
    test_determine_forces();
}
