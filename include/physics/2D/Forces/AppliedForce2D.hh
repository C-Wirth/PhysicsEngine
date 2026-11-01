#pragma once

#include <vector>

#include "physics/2D/AbstractElement2D.hh"
#include "AbstractForce2D.hh"
#include "math/VectorM.hh"

class AppliedForce2D : public AbstractForce2D
{
public:
    /**
     * Constructor
     * @param force the force vector
     */
    explicit AppliedForce2D(const VectorM<2> force)
        : force_(force)
    {
    }

    auto applyForce(AbstractElement2D& element) -> void override
    {
    }

private:
    VectorM<2> force_; // Newtons: Kg m/s^2
};
