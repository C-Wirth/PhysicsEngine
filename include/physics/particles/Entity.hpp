#pragma once

#include <ostream>

#include "math/VectorM.hpp"

#include "physics/physical/PhysicalProperties.hpp"


template <std::size_t N>
class Entity

/**
 * Virtual base class for all entities
 */
{

public:
    virtual ~Entity() = default;


    virtual auto print(std::ostream& stream, std::size_t depth) const -> std::ostream& = 0;

    virtual auto accumulateForce(const VectorM<N>& force) -> void = 0;
    virtual auto resetAccumulatedForces() -> void = 0;

    [[nodiscard]] virtual auto getMass() const -> double = 0;
};