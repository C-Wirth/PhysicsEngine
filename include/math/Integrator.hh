#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

#include "physics/2D/AbstractElement2D.hh"

/**
 * Integrators Singleton class
 */
class Integrator
{
public:
    Integrator(const Integrator&) = delete;
    Integrator& operator=(const Integrator&) = delete;

    /**
     * Retrieve the Singleton Integrator
     * @return
     */
    static Integrator& getInstance()
    {
        static Integrator instance;
        return instance;
    }

    auto setIntegrator(const std::string_view name) -> void
    {
        if (name == "Euler")
            step_function_ = &Integrator::EulerStep;
        else if (name == "Advanced Euler")
            step_function_ = &Integrator::AdvancedEulerStep;
        else if (name == "RK4")
            step_function_ = &Integrator::RK4Step;
        else
            throw std::invalid_argument("Unknown integrator: " + std::string{name});
    }

    // TODO Implement me
    auto stepIntegrator(AbstractElement2D& element, double dt) -> void
    {
        (this->*step_function_)(element, dt);
    }

    // TODO Implement me
    auto EulerStep(AbstractElement2D& element, double dt) -> void
    {
    }

    // TODO Implement me
    auto AdvancedEulerStep(AbstractElement2D& element, double dt) -> void
    {
    }

    // TODO Implement me
    auto RK4Step(AbstractElement2D& element, double dt) -> void
    {
    }

private:
    using StepFunction = void (Integrator::*)(AbstractElement2D&, double);

    Integrator()
    {
    }

    StepFunction step_function_{&Integrator::EulerStep};
};
