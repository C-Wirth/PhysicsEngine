#pragma once

#include <ostream>

class Entity
/**
 *
 * Virtual class for all entities
 *
 */

{
public:
    virtual ~Entity() = default;
    virtual auto print(std::ostream& stream, std::size_t depth) const -> std::ostream& = 0;
};