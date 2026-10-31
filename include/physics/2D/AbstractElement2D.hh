#pragma once

#include "math/VectorM.hh"

class AbstractElement2D
{
public:
    /**
     * destructor for AbstractForce2D
     */
    virtual ~AbstractElement2D() = default;

    /**
     * Adds a force vector to the element's underlying accumulatedForces_ vector
     * @param force
     */
    auto accumulateForce(const VectorM<2> force) -> void
    {
        accumulatedForces_ += force;
    };

    /**
     * Zeros out an element's accumulatedForces_ vector
     */
    auto resetAccumulatedForces() -> void
    {
        accumulatedForces_[0] = 0;
        accumulatedForces_[1] = 0;
    }

private:
    VectorM<2> accumulatedForces_;
};
