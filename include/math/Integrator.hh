#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

#include "physics/2D/KinematicState2D.hh"

/**
 * Selects and runs the configured integration method.
 */
class Integrator
{
public:
    Integrator(const Integrator&) = delete;
    Integrator& operator=(const Integrator&) = delete;

    static auto getInstance() -> Integrator&
    {
        static Integrator instance;
        return instance;
    }

    auto setIntegrator(const std::string_view name) -> void
    {
        if (name == "Euler")
            step_function_ = &Integrator::SemiImplicitEulerStep;
        else if (name == "Improved Euler")
            step_function_ = &Integrator::ImprovedEulerStep;
        else if (name == "RK4")
            step_function_ = &Integrator::RK4Step;
        else
            throw std::invalid_argument("Unknown integrator: " + std::string{name});
    }

    auto stepIntegrator(KinematicState2D& state, const double dt) const -> void
    {
        step_function_(state, dt);
    }

    static auto SemiImplicitEulerStep(KinematicState2D& state, const double dt) -> void
    {
        state.velocity = state.velocity + state.acceleration * dt;;
        state.position = state.position + state.velocity * dt;
    }

    static auto ImprovedEulerStep(KinematicState2D& state, const double dt) -> void
    {
        const auto velocity_next = state.velocity + state.acceleration * dt;
        VectorM<2> average_velocity = (state.velocity + velocity_next) * 0.5;
        const auto position_next = state.position + average_velocity * dt;

        state.velocity = velocity_next;
        state.position = position_next;
    }

    static auto RK4Step(KinematicState2D&, double) -> void
    {
        // TODO Implement RK4.
    }

private:
    using StepFunction = void (*)(KinematicState2D&, double);

    Integrator() = default;

    StepFunction step_function_{&Integrator::SemiImplicitEulerStep};
};
