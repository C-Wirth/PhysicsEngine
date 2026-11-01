#pragma once

#include <string>

#include "math/VectorM.hh"
#include "AbstractElement2D.hh"
#include "KinematicState2D.hh"

class Particle2D : public AbstractElement2D
{
public:
    /**
     * constructor for Particle2D with initialized KinematicState2D
     * @param name the string name of the Particle
     * @param ks_2d the Kinematic State.
     */
    explicit Particle2D(const std::string& name, const KinematicState2D& ks_2d)
        : AbstractElement2D(name), ks_2d_(ks_2d)

    {
    }

    /**
     * Set the value for the acceleration VectorM in the underlying KinematicState2D
     * @param acceleration
     */
    auto set_acceleration(const VectorM<2>& acceleration) -> void
    {
        ks_2d_.acceleration = acceleration;
    }

    /**
     * Set the value for the velocity VectorM in the underlying KinematicState2D
     * @param velocity
     */
    auto set_velocity(const VectorM<2>& velocity) -> void
    {
        ks_2d_.velocity = velocity;
    }


    /**
     * Set the value for the position VectorM in the underlying KinematicState2D
     * @param position
     */
    auto set_position(const VectorM<2>& position) -> void
    {
        ks_2d_.position = position;
    }

    /**
     * retrieve the acceleration of the underlying KinematicState2D
     * @return VectorM<2>
     */
    [[nodiscard]] auto get_acceleration() const -> VectorM<2>
    {
        return ks_2d_.acceleration;
    }

    /**
     * retrieve the velocity of the underlying KinematicState2D
     * @return VectorM<2>
     */
    [[nodiscard]] auto get_velocity() const -> VectorM<2>
    {
        return ks_2d_.velocity;
    }

    /**
     * retrieve the position of the underlying KinematicState2D
     * @return VectorM<2>
     */
    [[nodiscard]] auto get_position() const -> VectorM<2>
    {
        return ks_2d_.position;
    }

private:
    KinematicState2D ks_2d_;
};
