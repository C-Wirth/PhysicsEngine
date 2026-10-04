#include <memory>

#include "physics/forces/Force.hpp"
#include "math/VectorM.hpp"
#include "physics/particles/Particle2D.hpp"

class Gravity2D : public Force<2>
{
public:
    Gravity2D(
        const VectorM<2> f_gravity = VectorM<2>(std::array<double, 2>{0.0, -9.8})
    )
        : f_gravity_(f_gravity)
    {
    }


/**
 * f = ma
 * a = g = 9.8 m/s^2
 * → f = m * g
 */
auto applyForce(std::vector<std::unique_ptr<Entity<2>>>& entities) -> void override    {



        for (auto& e : entities)
        {
            e->accumulateForce(f_gravity_ * e->getMass());
        }

    }

private:
    const VectorM<2> f_gravity_;
};
