#pragma once

#include <vector>

#include "physics/particles/Entity.hpp"

template <std::size_t N>
class Force
{
public:
    virtual ~Force() = default;
    virtual auto applyForce(std::vector<std::unique_ptr<Entity<N>>>& entities) -> void = 0;
};
