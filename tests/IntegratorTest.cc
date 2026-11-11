#include <iostream>
#include <array>
#include <cassert>
#include <cmath>


#include "physics/2D/Particle2D.hh"
#include "math/VectorM.hh"
#include "physics/2D/KinematicState2D.hh"
#include "math/Integrator.hh"


static void testGetInstance()
{
    Integrator::getInstance().setIntegrator("Euler");
    Integrator::getInstance().setIntegrator("Improved Euler");
    Integrator::getInstance().setIntegrator("RK4");

    bool caught = false;
    try
    {
        Integrator::getInstance().setIntegrator("ABC");
    }
    catch (const std::invalid_argument&)
    {
        caught = true;
    }
    assert(caught);
}


static void testStepEuler()
{
    auto dt = 1.0 / 60.0;

    std::string name("particle_1");

    const KinematicState2D ks_2d{
        .acceleration = VectorM<2>(std::array<double, 2>{0, 0}),
        .velocity = VectorM<2>(std::array<double, 2>{1, 1}),
        .position = VectorM<2>(std::array<double, 2>{2, 2})
    };

    Particle2D particle("particle_1", ks_2d, 2.0);

    Integrator::getInstance().setIntegrator("Euler");

    Integrator::getInstance().stepIntegrator(particle.get_kinematic_state(), dt);

    assert(particle.get_acceleration()==VectorM(std::array<double, 2>{0.0,0.0}));
    assert(particle.get_velocity()==VectorM(std::array<double, 2>{1.0,1.0}));

    const auto position = particle.get_position();

    const double expected_position = 2.0 + dt;
    constexpr double tolerance = 1e-9;
    assert(std::abs(position[0] - expected_position) < tolerance);
    assert(std::abs(position[1] - expected_position) < tolerance);
}


static void testStepImprovedEuler()
{
    const auto dt = 1.0 / 60.0;

    std::string name("particle_1");

    const KinematicState2D ks_2d{
        .acceleration = VectorM<2>(std::array<double, 2>{0, 0}),
        .velocity = VectorM<2>(std::array<double, 2>{1, 1}),
        .position = VectorM<2>(std::array<double, 2>{2, 2})
    };

    Particle2D particle("particle_1", ks_2d, 2.0);

    Integrator::getInstance().setIntegrator("Improved Euler");

    Integrator::getInstance().stepIntegrator(particle.get_kinematic_state(), dt);

    assert(particle.get_acceleration()==VectorM(std::array<double, 2>{0.0,0.0}));
    assert(particle.get_velocity()==VectorM(std::array<double, 2>{1.0,1.0}));

    const auto position = particle.get_position();

    const double expected_position = 2.0 + dt;
    constexpr double tolerance = 1e-9;
    assert(std::abs(position[0] - expected_position) < tolerance);
    assert(std::abs(position[1] - expected_position) < tolerance);
}


int main()
{
    testGetInstance();
    testStepEuler();
    testStepImprovedEuler();
};
