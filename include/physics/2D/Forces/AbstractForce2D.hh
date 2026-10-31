#pragma once

#include "physics/2D/AbstractElement2D.hh"

class AbstractForce2D
{
public:

    /**
     * Abstract constructor to be overwritten
     */
    explicit AbstractForce2D();
    virtual ~AbstractForce2D() = default;

    /**
     * Abstract applyForce function.
     * It mutates the element directly
     * Every child class must implement this function
     * @param element
     */
    virtual auto applyForce(AbstractElement2D& element) -> void;

};
