#pragma once

#include <ostream>

#include "math/VectorM.hpp"

#include "physics/physical/PhysicalProperties.hpp"
#include "physics/state/KinematicState2D.hpp"


template <std::size_t N>
class Entity

/**
 * Virtual base class for all entities
 */
{

public:
    virtual ~Entity() = default;


    virtual auto print(std::ostream& stream, std::size_t depth) const -> std::ostream& = 0;

    virtual auto state() -> KinematicState2D& = 0;         // mutable
    [[nodiscard]] virtual auto state() const -> const KinematicState2D& = 0;  // read-only

    virtual auto accumulateForce(const VectorM<N>& force) -> void = 0;
    virtual auto resetAccumulatedForces() -> void = 0;
    virtual auto calculateAcceleration() -> void = 0;

    [[nodiscard]] virtual auto getMass() const -> double = 0;
};