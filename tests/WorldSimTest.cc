#include <cassert>
#include <utility>

#include <toml++/toml.hpp>

#include "simulation/WorldSim.hh"

static auto test_parse_config_table() -> void
{
    toml::table config_table{
        {
            "Simulation", toml::table{
                {"step_rate_hz", 60.0}
            }
        },
        {
            "Particle2D", toml::table{
                {
                    "particle1", toml::table{
                        {"acceleration", toml::array{0.0, 0.0}},
                        {"velocity", toml::array{-1.0, -1.0}},
                        {"position", toml::array{0.0, 0.0}}
                    }
                },
                {
                    "particle2", toml::table{
                        {"acceleration", toml::array{0.0, 0.0}},
                        {"velocity", toml::array{1.0, 1.0}},
                        {"position", toml::array{1.0, 1.0}}
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
                    {"step_rate_hz", 60.0}
                }
            },
            {
                "Particle2D", toml::table{
                    {
                        "particle1", toml::table{
                            {"acceleration", toml::array{0.0, 0.0}},
                            {"velocity", toml::array{-1.0, -1.0}},
                            {"position", toml::array{0.0, 0.0}}
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

        // t_0 : time = 0.0 seconds
        // applied once and removed; the one-second force also starts applying.
        sim.stepSimulation();
        assert(sim.appliedForceSchedule.size() == 1);
        assert(sim.appliedForceSchedule[0].timestamp == 0.0);

        // t_1 : time = 1/60 seconds
        sim.stepSimulation();
        assert(sim.appliedForceSchedule.size() == 1);
        assert(sim.elements_2d[0]->element_2d->getAccumulatedForces()[0] == 3.0);

        // Complete 60 steps total. The final force evaluation is at t = 59/60 s.
        for (auto idx = 2; idx < 60; idx++)
        {
            sim.stepSimulation();
            assert(sim.appliedForceSchedule.size() == 1);
        }

        // Step 61 evaluates forces at t = 1 second, so the force expires.
        sim.stepSimulation();
        assert(sim.appliedForceSchedule.empty());
    }
}

int main()
{
    test_parse_config_table();
    test_determine_forces();
}
