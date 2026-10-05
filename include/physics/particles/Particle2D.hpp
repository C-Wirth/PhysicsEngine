#pragma once

#include <ostream>
#include <string>

#include "physics/particles/Entity.hpp"
#include "physics/state/KinematicState2D.hpp"
#include "physics/physical/PhysicalProperties.hpp"
#include "physics/geometry/Geometry2D.hpp"

#include "math/VectorM.hpp"

#include "util/IndentStream.hpp"

class Particle2D : public Entity<2>
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

    [[nodiscard]] auto state() const -> const KinematicState2D& override { return state_; }
    auto state() -> KinematicState2D& override { return state_; }
    [[nodiscard]] auto properties() const -> const PhysicalProperties& { return properties_; }
    [[nodiscard]] auto geometry() const -> const Geometry2D& { return geometry_; }


    [[nodiscard]] auto getMass() const -> double override { return properties_.mass(); }


    auto accumulateForce(const VectorM<2>& force) -> void override
    {
        accumulatedForces_ += force;
    }

    auto calculateAcceleration() -> void override
    {
        state_.updateAcceleration(accumulatedForces_ / getMass());
    }

    auto resetAccumulatedForces() -> void override
    {
        accumulatedForces_ = VectorM<2>();
    }


    auto print(std::ostream& stream, size_t depth) const -> std::ostream& override
    {
        stream << Indent(depth) << "Particle2D \"" << name << "\": [\n";
        ::print(stream, state_, depth + 1);
        //stream << Indent(depth + 1) << "geometry: " << geometry_ << ",\n";
        //stream << Indent(depth + 1) << "properties: " << properties_ << "\n";
        stream << Indent(depth) << "]";
        return stream;
    }

    std::string name;

private:
    KinematicState2D state_;
    PhysicalProperties properties_;
    Geometry2D geometry_;
    VectorM<2> accumulatedForces_;
};

inline auto operator<<(std::ostream& stream, const Particle2D& particle) -> std::ostream&
{
    return particle.print(stream, 0);
}
