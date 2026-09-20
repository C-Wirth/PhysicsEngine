#include "simulation/WorldSim.hpp"


WorldSim::WorldSim(const WorldConfig& config)
    :
    timestep_(config.timestep)
{
}

auto WorldSimStep() -> void
{
        // 1. determine forces

        // 2. Accumulate forces

        // 3. Calculate acceleration (lowest measured Kinematic)

        // 4. Run numerical Integrator

        // 5. Update state

        // 6. state is now at t + Δt
}