#pragma once

#include <string>
#include "math/VectorM.hh"
#include "physics/KinematicState2D.hh"

class Particle2D
{
public:
    /**
     * constructor for Particle2D with initialized KinematicState2D
     * @param ks_2d
     */
    explicit Particle2D(const KinematicState2D& ks_2d, const std::string name)
        : ks_2d_(ks_2d), name_(name)
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

    /**
     *  retrieve the Particle2D's name
     * @return std::string name_
     */
    [[nodiscard]] auto get_name() const -> std::string
    {
        return name_;
    }

    /**
     * set the particle 2D's name after construction
     * @param name std::string
     */
    auto set_name(const std::string& name) -> void
    {
        name_ = name;
    }

private:
    KinematicState2D ks_2d_;
    std::string name_;
};
