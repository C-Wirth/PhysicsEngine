#include "simulation/WorldSim.hpp"

#include <utility>
#include "simulation/WorldConfig.hpp"

#include "physics/forces/Gravity.hpp"


WorldSim::WorldSim(WorldConfig config)
    :
    config_(std::move(config))
{
}

auto WorldSim::WorldSimStep() -> void

{
        // 1. determine forces

        //.1a gravity
        auto gravity_2d = Gravity2D();


        // 2. Accumulate forces

        //2.a accumulate gravity
        gravity_2d.applyForce(config_.entities);

        // TODO accumulate other forces


        // 3. Calculate acceleration (lowest measured Kinematic)

        // 4. Run numerical Integrator

        // 5. Update state

        // 6. state is now at t + Δt

        // 6.a reset accumulators
}
