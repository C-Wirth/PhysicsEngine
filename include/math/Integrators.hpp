#pragma once

#include "math/VectorM.hpp"
#include "physics/state/KinematicState2D.hpp"

class NumericalIntegrator
{
    /**
     * Default Constructor
     */
     NumericalIntegrator()
    = default;

public:
    static auto IntegrateEuler(KinematicState2D& state, const double dt) -> void
    {
        const VectorM<2> v = state.velocity() + state.acceleration() * dt;
        const VectorM<2> p = state.position() + state.velocity() * dt;

        state.updateVelocity(v);
        state.updatePosition(p);
    }
};
