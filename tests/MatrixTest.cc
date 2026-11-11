#include <cassert>
#include "math/Matrix.hh"

static auto testIdentityConstructor()
{
    auto m1 = Matrix<1, 1>::Identity();
    assert((m1[0,0] == 1));
    auto m2 = Matrix<2, 2>::Identity();
    assert((m2[0,0] == 1));
    assert((m2[0,1] == 0));
    assert((m2[1,0] == 0));
    assert((m2[1,1] == 1));
    auto m3 = Matrix<3, 3>::Identity();
    assert((m3[0,0] == 1));
    assert((m3[0,1] == 0));
    assert((m3[0,2] == 0));
    assert((m3[1,0] == 0));
    assert((m3[1,1] == 1));
    assert((m3[1,2] == 0));
    assert((m3[1,2] == 0));
    assert((m3[2,2] == 1));
    assert((m3[1,3] == 0));
    auto m4 = Matrix<4, 4>::Identity();
    assert((m4[0,0] == 1));
    assert((m4[0,1] == 0));
    assert((m4[0,2] == 0));
    assert((m4[0,3] == 0));
    assert((m4[1,0] == 0));
    assert((m4[1,1] == 1));
    assert((m4[1,2] == 0));
    assert((m4[1,3] == 0));
    assert((m4[2,0] == 0));
    assert((m4[2,1] == 0));
    assert((m4[2,2] == 1));
    assert((m4[2,3] == 0));
    assert((m4[3,0] == 0));
    assert((m4[3,1] == 0));
    assert((m4[3,2] == 0));
    assert((m4[3,3] == 1));
}

int main()
{
    testIdentityConstructor();
}
