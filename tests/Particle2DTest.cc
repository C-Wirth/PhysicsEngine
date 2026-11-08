#include <array>
#include <string>

#include "math/VectorM.hh"
#include "../include/physics/2D/KinematicState2D.hh"
#include "../include/physics/2D/Particle2D.hh"

static void test_particle2d_constructor()
{
    VectorM<2> a = VectorM<2>(std::array<double, 2>{0, 0});
    VectorM<2> v = VectorM<2>(std::array<double, 2>{1, 1});
    VectorM<2> p = VectorM<2>(std::array<double, 2>{2, 2});
    const auto mass = 2.0;

    const KinematicState2D ks_2d{.acceleration = a, .velocity = v, .position = p};
    Particle2D particle("particle1", ks_2d, mass);

    assert(particle.get_acceleration()==a);
    assert(particle.get_acceleration()!=v);
    assert(particle.get_acceleration()!=p);

    assert(particle.get_velocity()==v);
    assert(particle.get_velocity()!=a);
    assert(particle.get_velocity()!=p);

    assert(particle.get_position()==p);
    assert(particle.get_position()!=a);
    assert(particle.get_position()!=v);
}

static void test_set_ks2d_values()
{
    const auto v1 = VectorM<2>(std::array<double, 2>{0, 0});
    const auto v2 = VectorM<2>(std::array<double, 2>{1, 1});
    constexpr auto mass = 2.0;

    constexpr KinematicState2D ks_2d{};
    Particle2D particle("particle1", ks_2d, mass);

    assert(particle.get_acceleration()==v1);
    assert(particle.get_velocity()==v1);
    assert(particle.get_position()==v1);

    assert(particle.get_acceleration()!=v2);
    assert(particle.get_velocity()!=v2);
    assert(particle.get_position()!=v2);

    particle.set_acceleration(v2);
    particle.set_velocity(v2);
    particle.set_position(v2);

    assert(particle.get_acceleration()==v2);
    assert(particle.get_velocity()==v2);
    assert(particle.get_position()==v2);

    assert(particle.get_acceleration()!=v1);
    assert(particle.get_velocity()!=v1);
    assert(particle.get_position()!=v1);
}

static void test_get_particle2d_name()
{
    const std::string name("particle_1");

    const auto a = VectorM<2>(std::array<double, 2>{0, 0});
    const auto v = VectorM<2>(std::array<double, 2>{1, 1});
    const auto p = VectorM<2>(std::array<double, 2>{2, 2});
    constexpr auto mass = 2.0;


    const KinematicState2D ks_2d{.acceleration = a, .velocity = v, .position = p};

    Particle2D particle(name, ks_2d, mass);

    assert(particle.get_name()=="particle_1");
    assert(particle.get_name()!="particle_2");
    assert(!particle.get_name().empty());
}


static void test_set_particle2d_name()
{
    std::string name("particle_1");

    VectorM<2> a = VectorM<2>(std::array<double, 2>{0, 0});
    VectorM<2> v = VectorM<2>(std::array<double, 2>{1, 1});
    VectorM<2> p = VectorM<2>(std::array<double, 2>{2, 2});
    constexpr auto mass = 2.0;

    const KinematicState2D ks_2d{.acceleration = a, .velocity = v, .position = p};

    Particle2D particle(name, ks_2d, mass);
    particle.set_name("particle_2");


    assert(particle.get_name()!="particle_1");
    assert(particle.get_name()=="particle_2");
    assert(!particle.get_name().empty());
}



int main()
{
    test_particle2d_constructor();
    test_set_ks2d_values();
    test_get_particle2d_name();
    test_set_particle2d_name();
}
