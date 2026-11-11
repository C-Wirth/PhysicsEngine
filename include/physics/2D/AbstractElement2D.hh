#pragma once

#include <string>
#include <utility>

#include "math/VectorM.hh"
#include "KinematicState2D.hh"

class AbstractElement2D
{
public:
    /**
     * destructor for AbstractForce2D
     */
    virtual ~AbstractElement2D() = default;

    /**
     * Constructor with name and kinematic state
     * @param name the defining name of an element
     * @param kinematic_state the kinematic state of an element
     * @param mass the mass (KG) of an object
     */
    explicit AbstractElement2D(std::string name, const KinematicState2D& kinematic_state, double mass)
        : name_(std::move(name)), kinematic_state_(kinematic_state), mass_(mass)
    {
    }

    auto set_acceleration(const VectorM<2>& acceleration) -> void
    {
        kinematic_state_.acceleration = acceleration;
    }

    auto set_velocity(const VectorM<2>& velocity) -> void
    {
        kinematic_state_.velocity = velocity;
    }

    auto set_position(const VectorM<2>& position) -> void
    {
        kinematic_state_.position = position;
    }

    [[nodiscard]] auto get_acceleration() const -> VectorM<2>
    {
        return kinematic_state_.acceleration;
    }

    [[nodiscard]] auto get_velocity() const -> VectorM<2>
    {
        return kinematic_state_.velocity;
    }

    [[nodiscard]] auto get_position() const -> VectorM<2>
    {
        return kinematic_state_.position;
    }

    [[nodiscard]] auto get_kinematic_state() -> KinematicState2D&
    {
        return kinematic_state_;
    }

    [[nodiscard]] auto get_kinematic_state() const -> const KinematicState2D&
    {
        return kinematic_state_;
    }

    [[nodiscard]] auto get_mass() const -> double
    {
        return mass_;
    }

    auto set_mass(const double m) -> void
    {
        mass_ = m;
    }

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

    [[nodiscard]] auto getAccumulatedForces() const -> VectorM<2>
    {
        return accumulatedForces_;
    }

    [[nodiscard]] auto get_name() const -> const std::string&
    {
        return name_;
    }

    auto set_name(const std::string& name) -> void
    {
        name_ = name;
    }

private:
    std::string name_;
    KinematicState2D kinematic_state_;
    VectorM<2> accumulatedForces_;
    double mass_;
};
