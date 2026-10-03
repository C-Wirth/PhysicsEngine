#include "simulation/WorldSim.hpp"

#include <utility>
#include "simulation/WorldConfig.hpp"


WorldSim::WorldSim(WorldConfig config)
    :
    config_(std::move(config))
{
}

auto WorldSim::WorldSimStep() -> void
{
        // 1. determine forces

        // 2. Accumulate forces

        // 3. Calculate acceleration (lowest measured Kinematic)

        // 4. Run numerical Integrator

        // 5. Update state

        // 6. state is now at t + Δt
}