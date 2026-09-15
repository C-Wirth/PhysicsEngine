#pragma once

#include <ostream>

#include "math/VectorM.hpp"
#include "util/IndentStream.hpp"

struct KinematicState2D
{
    KinematicState2D(
        VectorM<2> position,
        VectorM<2> velocity,
        VectorM<2> acceleration)
        : position_(position),
          velocity_(velocity),
          acceleration_(acceleration)
    {
    }

    [[nodiscard]] auto position() const -> const VectorM<2>&
    {
        return position_;
    }

    [[nodiscard]] auto velocity() const -> const VectorM<2>&
    {
        return velocity_;
    }

    [[nodiscard]] auto acceleration() const -> const VectorM<2>&
    {
        return acceleration_;
    }


private:
    VectorM<2> position_;
    VectorM<2> velocity_;
    VectorM<2> acceleration_;
};


static auto print(std::ostream& stream, const KinematicState2D& state, const size_t depth) -> std::ostream&
{
    stream << Indent(depth) << "Kinematics: [\n";
    stream << Indent(depth + 1) <<  "Position: ";
    print(stream, state.position(), 0);
    stream << ",\n" << Indent(depth + 1) <<  "Velocity: ";
    print(stream, state.velocity(), 0);
    stream << ",\n" << Indent(depth + 1) <<  "Acceleration: ";
    print(stream, state.acceleration(), 0);
    stream << "\n" << Indent(depth) << "]\n";

    return stream;
}

inline auto operator<<(std::ostream& stream, const KinematicState2D& state) -> std::ostream& {
    return print(stream, state, 0);
}

