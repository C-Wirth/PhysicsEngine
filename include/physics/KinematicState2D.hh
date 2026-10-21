#pragma once

#include "math/VectorM.hh"

struct KinematicState2D
{
    VectorM<2> acceleration{};
    VectorM<2> velocity{};
    VectorM<2> position{};
};