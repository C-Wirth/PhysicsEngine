#include <iostream>
#include <memory>
#include <vector>

#include "simulation/WorldSim.hpp"
#include "simulation/WorldConfig.hpp"

#include "math/VectorM.hpp"
#include "physics/state/KinematicState2D.hpp"
#include "physics/geometry/Geometry2D.hpp"
#include "physics/particles/Entity.hpp"
#include "physics/physical/PhysicalProperties.hpp"
#include "physics/particles/Particle2D.hpp"

auto main() -> int
{
    std::vector<std::unique_ptr<Entity<2>>> particles;

    particles.push_back(std::make_unique<Particle2D>(
        KinematicState2D(
            VectorM<2>(std::array<double, 2>{0.0, 0.0}),
            VectorM<2>(std::array<double, 2>{0.0, 0.0}),
            VectorM<2>(std::array<double, 2>{0.0, 0.0})
        ),
        PhysicalProperties(1.0),
        Geometry2D(1.0, 1.0)
    ));

    particles.push_back(std::make_unique<Particle2D>(
        KinematicState2D(
            VectorM<2>(std::array<double, 2>{1.0, 1.0}),
            VectorM<2>(std::array<double, 2>{1.0, 1.0}),
            VectorM<2>(std::array<double, 2>{1.0, 1.0})
        ),
        PhysicalProperties(2.0),
        Geometry2D(2.0, 2.0)
    ));

    WorldSim world(WorldConfig(std::move(particles)));

    std::cout << world.GetConfig();


    return 0;
}