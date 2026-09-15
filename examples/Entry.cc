#include <iostream>
#include <utility>


#include "simulation/WorldSim.hpp"
#include "simulation/WorldConfig.hpp"

#include "math/VectorM.hpp"
#include "physics/state/KinematicState2D.hpp"
#include "physics/geometry/Geometry2D.hpp"
#include "physics/physical/PhysicalProperties.hpp"
#include "physics/particles/Particle2D.hpp"

auto main() -> int
{

    const std::vector<Particle2D> particles{
        Particle2D(
            KinematicState2D(
                VectorM<2>(std::array<double, 2>{0.0, 0.0}),
                VectorM<2>(std::array<double, 2>{0.0, 0.0}),
                VectorM<2>(std::array<double, 2>{0.0, 0.0})
            ),
            PhysicalProperties(1.0),
            Geometry2D(1.0,1.0)
        ),

        Particle2D(
            KinematicState2D(
                VectorM<2>(std::array<double, 2>{1.0, 1.0}),
                VectorM<2>(std::array<double, 2>{1.0, 1.0}),
                VectorM<2>(std::array<double, 2>{1.0, 1.0})
            ),
            PhysicalProperties(2.0),
            Geometry2D(2.0,2.0)
        ),
    };

    const WorldConfig config(particles);

    WorldSim world(config);

    std::cout << config << "\n";

    return 0;
}
