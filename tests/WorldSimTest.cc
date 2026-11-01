#include <cassert>
#include <utility>

#include <toml++/toml.hpp>

#include "simulation/WorldSim.hh"

static auto test_parse_config_table() -> void
{
    toml::table config_table{
        {"Simulation", toml::table{
            {"step_rate_hz", 60.0}
        }},
        {"Particle2D", toml::table{
            {"particle1", toml::table{
                {"acceleration", toml::array{0.0, 0.0}},
                {"velocity", toml::array{-1.0, -1.0}},
                {"position", toml::array{0.0, 0.0}}
            }},
            {"particle2", toml::table{
                {"acceleration", toml::array{0.0, 0.0}},
                {"velocity", toml::array{1.0, 1.0}},
                {"position", toml::array{1.0, 1.0}}
            }}
        }},
        {"AppliedForce2D", toml::table{
            {"force1", toml::table{
                {"force", toml::array{1.0, 1.0}},
                {"target_particles", toml::array{"particle1"}},
                {"start_and_duration_pairs", toml::array{
                    toml::array{0.0, 0.0},
                    toml::array{5.0, 0.0}
                }}
            }}
        }}
    };

    const WorldSim sim{std::move(config_table)};

    assert(sim.step_rate_hz == 60.0);
    assert(sim.elements_2d.size() == 2);
    assert(sim.appliedForceSchedule.size() == 2);
    assert(sim.appliedForceSchedule[0].target_element_name == "particle1");
    assert(sim.appliedForceSchedule[0].timestamp == 0.0);
    assert(sim.appliedForceSchedule[1].timestamp == 5.0);
}

int main()
{
    test_parse_config_table();
}
