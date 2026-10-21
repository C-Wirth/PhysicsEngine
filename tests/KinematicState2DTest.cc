#include <cassert>
#include <array>

#include "math/VectorM.hh"
#include "physics/KinematicState2D.hh"

static void test_ks2d_constructor()
{
    KinematicState2D ks1{};

    VectorM<2> v1{};
    assert(ks1.acceleration==v1);
    assert(ks1.velocity==v1);
    assert(ks1.position==v1);

    KinematicState2D ks2 {
        VectorM(std::array<double, 2>{1.0, 2.0}),
        VectorM<2>{},
    };

    assert(ks2.acceleration==VectorM<2>(std::array<double, 2>{1.0, 2.0}));
    assert(ks2.velocity==VectorM<2>{});
}

static void test_ks2d_update()
{

    KinematicState2D ks1{};

    VectorM<2> v1{std::array<double, 2>{1.0, 2.0}};
    ks1.acceleration = v1;

    assert(ks1.acceleration==v1);

    assert(ks1.acceleration[0]==1.0);
    assert(ks1.acceleration[1]==2.0);
}

int main()
{
     test_ks2d_constructor();
    test_ks2d_update();
}
