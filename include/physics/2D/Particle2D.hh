#pragma once

#include <string>

#include "AbstractElement2D.hh"
#include "KinematicState2D.hh"

class Particle2D : public AbstractElement2D
{
public:
    /**
     * constructor for Particle2D with initialized KinematicState2D
     * @param name the string name of the Particle
     * @param ks_2d the Kinematic State.
     * @param mass mass (KG) of particle
     */
    explicit Particle2D(const std::string& name, const KinematicState2D& ks_2d, double mass)
        : AbstractElement2D(name, ks_2d, mass)
    {
    }
};
