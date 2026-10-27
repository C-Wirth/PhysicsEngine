#include <array>

#include "math/VectorM.hh"
#include "physics/KinematicState2D.hh"
#include "physics/Particle2D.hh"

static void test_particle2d_constructor()
{
    VectorM<2> a = VectorM<2>(std::array<double, 2>{0, 0});
    VectorM<2> v = VectorM<2>(std::array<double, 2>{1, 1});
    VectorM<2> p = VectorM<2>(std::array<double, 2>{2, 2});

    const KinematicState2D ks_2d{.acceleration = a, .velocity = v, .position = p};
    Particle2D particle(ks_2d);

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

    constexpr KinematicState2D ks_2d{};
    Particle2D particle(ks_2d);

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

int main()
{
    test_particle2d_constructor();
    test_set_ks2d_values();
}
