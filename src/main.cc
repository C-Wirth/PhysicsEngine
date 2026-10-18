#include <iostream>

#include "math/VectorM.hh"

auto main() -> int
{
    std::array<double, 3> a = {1.0, 2.0, 3.0};
    VectorM<3> v1(a);
    VectorM<3> v2{};

    VectorM<3> v3 = v1 + v1;

    return 0;
}
