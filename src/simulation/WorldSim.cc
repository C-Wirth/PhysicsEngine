#include "simulation/WorldSim.hpp"

#include <utility>

#include "math/Integrators.hpp"
#include "simulation/WorldConfig.hpp"

#include "physics/forces/Gravity.hpp"
#include "physics/particles/Particle2D.hpp"


/**
 * Constructor
 * @param config config the user set configuration WorldConfig object
 */
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
        for (const auto& e : config_.entities)
        {
            e->calculateAcceleration();
        }

        // 4. Run numerical Integrator
        for (const auto& e : config_.entities)
        {
            NumericalIntegrator::IntegrateEuler(e->state(), config_.timestep);
        }


        // 5. state is now at t + Δt

        // 5.a reset accumulators
        for (const auto& e : config_.entities)
        {
            e->resetAccumulatedForces();
        }
}
