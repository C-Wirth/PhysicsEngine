#pragma once

#include "math/VectorM.hh"

class KinematicState2D
{
public:
    /**
     * Base constructor with no args
     */
    explicit KinematicState2D()
        :
        acceleration_(VectorM<2>()),
        velocity_(VectorM<2>()),
        position_(VectorM<2>())
    {
    }


    /**
     * constructor with defines kinematic state vectors
     * this gives ownership of the vectors to the Kinematic state.
     * @param acceleration a VectorM<2D>
     * @param velocity a VectorM<2D>
     * @param position a VectorM<2D>
     */
    KinematicState2D(
        const VectorM<2>& acceleration,
        const VectorM<2>& velocity,
        const VectorM<2>& position
    )
        :
        acceleration_(acceleration),
        velocity_(velocity),
        position_(position)
    {
    }



private:
    VectorM<2> acceleration_;
    VectorM<2> velocity_;
    VectorM<2> position_;
};
