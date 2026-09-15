#pragma once

#include <iomanip>
#include <ostream>


#include "math/VectorM.hpp"
#include"physics/state/KinematicState2D.hpp"
#include "physics/physical/PhysicalProperties.hpp"
#include "physics/geometry/Geometry2D.hpp"

class Particle2D
{

public:
    Particle2D(
        const KinematicState2D& state,
        const PhysicalProperties& properties,
        const Geometry2D& geometry
    )
    : state_(state), properties_(properties), geometry_(geometry)
    {
    }

    [[nodiscard]] auto state() const -> KinematicState2D
    {
        return state_;
    }


    [[nodiscard]] auto properties() const -> PhysicalProperties
    {
        return properties_;
    }

    [[nodiscard]] auto geometry() const -> Geometry2D
    {
        return geometry_;
    }

    std::string name;


private:
    KinematicState2D state_;
    PhysicalProperties properties_;
    Geometry2D geometry_;

};


static auto print(std::ostream& stream, const Particle2D& particle, const size_t depth, const size_t idx) -> std::ostream&
{
    stream << Indent(depth) << "Particle2D [" << idx << "]:\n";
    print(stream, particle.state(), depth +1);
    //geometry.print(stream, depth +1);
    //properties.print(stream, depth +1);
    stream << Indent(depth) << "]";

    return stream;
}

inline auto operator<<(std::ostream& stream, const Particle2D& particle) -> std::ostream&
{
    return print(stream, particle, 0, 0);
}
