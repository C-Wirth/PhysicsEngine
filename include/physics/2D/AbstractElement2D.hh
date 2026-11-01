#pragma once

#include <string>
#include <utility>

#include "math/VectorM.hh"

class AbstractElement2D
{
public:
    /**
     * destructor for AbstractForce2D
     */
    virtual ~AbstractElement2D() = default;

    /**
     * Constructor with name field
     * @param name the defining name of an element
     */
    explicit AbstractElement2D(std::string name)
        : name_(std::move(name))
    {
    }


    /**
     * Adds a force vector to the element's underlying accumulatedForces_ vector
     * @param force
     */
    auto accumulateForce(const VectorM<2> force) -> void
    {
        accumulatedForces_ += force;
    };

    /**
     * Zeros out an element's accumulatedForces_ vector
     */
    auto resetAccumulatedForces() -> void
    {
        accumulatedForces_[0] = 0;
        accumulatedForces_[1] = 0;
    }

    [[nodiscard]] auto get_name() const -> const std::string&
    {
        return name_;
    }

    auto set_name(const std::string& name) -> void
    {
        name_ = name;
    }

private:
    std::string name_;
    VectorM<2> accumulatedForces_;
};
