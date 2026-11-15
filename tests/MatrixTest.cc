#include <cassert>
#include "math/Matrix.hh"
#include "math/VectorM.hh"

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

static auto testZeroConstructor()
{
    auto m = Matrix<1, 1>::Zero();
    for (std::size_t row = 0; row < m.rows(); row++)
    {
        for (std::size_t col = 0; col < m.columns(); col++)
        {
            assert((m[row, col] == 0.0));
        }
    }
}


static auto testMatMul()
{
    auto m1 = Matrix<2, 2>{std::array<double, 4>{1, 2, 3, 4}};
    const auto m2 = Matrix<2, 2>{std::array<double, 4>{1, 0, 0, 1}};

    // matmul against an identity matrix
    auto m3 = m1.matMul(m2);
    assert((m3[0,0] == 1));
    assert((m3[0,1] == 2));
    assert((m3[1,0] == 3));
    assert((m3[1,1] == 4));

    auto m4 = m3.matMul(m3);
    assert((m4[0,0] == 7));
    assert((m4[0,1] == 10));
    assert((m4[1,0] == 15));
    assert((m4[1,1] == 22));
}

static auto testTranspose()
{
    auto m1 = Matrix<2, 2>{std::array<double, 4>{1, 2, 3, 4}};
    auto m2 = m1.T();

    assert((m2[0,0] == 1));
    assert((m2[0,1] == 3));
    assert((m2[1,0] == 2));
    assert((m2[1,1] == 4));

    auto m3 = Matrix<2, 3>{std::array<double, 6>{1, 2, 3, 4, 5, 6}};
    auto m4 = m3.T();
    assert((m4[0,0] == 1));
    assert((m4[0,1] == 4));
    assert((m4[1,0] == 2));
    assert((m4[1,1] == 5));
    assert((m4[2,0] == 3));
    assert((m4[2,1] == 6));
}

static auto testMatrixVectorMul()
{
    const auto m1 = Matrix<2, 3>{std::array<double, 6>{1, 2, 3, 4, 5, 6}};
    const auto v1 = VectorM<3>{std::array<double, 3>{7, 8, 9}};

    auto v2 = m1 * v1;

    assert((v2[0] == 50));
    assert((v2[1] == 122));
}


static auto testMatrixScalarMul()
{
    const auto m1 = Matrix<2, 3>{std::array{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}};

    auto m2 = m1 * -1.0;

    assert((m2[0,0] == -1.0));
    assert((m2[0,1] == -2.0));
    assert((m2[0,2] == -3.0));
    assert((m2[1,0] == -4.0));
    assert((m2[1,1] == -5.0));
    assert((m2[1,2] == -6.0));

    auto m3 = m2 * -3.0;

    assert((m3[0,0] == 3.0));
    assert((m3[0,1] == 6.0));
    assert((m3[0,2] == 9.0));
    assert((m3[1,0] == 12.0));
    assert((m3[1,1] == 15.0));
    assert((m3[1,2] == 18.0));
}

int main()
{
    testIdentityConstructor();
    testZeroConstructor();
    testMatMul();
    testTranspose();
    testMatrixVectorMul();
    testMatrixScalarMul();
}
