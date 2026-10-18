#include <array>
#include <cassert>
#include <typeinfo>
#include <stdexcept>
#include "math/VectorM.hh"

/**
 * test for valid operator[] overload for access
 */
static void test_element_access()
{
    VectorM<2> v(std::array<double, 2>{1.0, 2.0});

    assert(v[0] == 1.0);
    assert(v[1] == 2.0);
}


/**
 * test that an error is thrown when indexing under range
 */
static void test_out_of_bounds_under()
{
    VectorM<2> v(std::array<double, 2>{1.0, 2.0});

    bool threw = false;

    try
    {
        double x = v[-1];
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }

    assert(threw);
}


/**
 * test that an error is thrown when indexing over range
 */
static void test_out_of_bounds_over()
{
    VectorM<2> v(std::array<double, 2>{1.0, 2.0});

    bool threw = false;

    try
    {
        double x = v[2];
    }
    catch (const std::out_of_range&)
    {
        threw = true;
    }

    assert(threw);
}


/**
 * test for valid operator[] overload for update
 */
static void test_update_idx()
{
    VectorM<2> v(std::array<double, 2>{1.0, 2.0});

    double x = 3.0;
    v[0] = x;

    assert(v[0] == x);
}


/**
 * get the length of the templated VectorM
 */
static void test_len_method()
{
    constexpr VectorM<0> v{};
    assert(v.len() ==0);

    constexpr VectorM<10> p{};
    assert(p.len() ==10);
}

/**
 * tests the default constructor
 */
static void test_default_constructor()
{
    VectorM<2> v{};

    assert(v.len() == 2);

    assert(v[0] == 0 && v[1] == 0);

    v[0] = 1.0;
    assert(v[0] == 1.0);

    v[1] = 2.0;
    assert(v[1] == 2.0);
}


static void test_convert_parameter_to_double_quiet()
{
    VectorM<3> v(std::array<double, 3>{1, 1e-5, 2.0});

    assert(typeid(v[0]) == typeid(double));
    assert(typeid(v[1]) == typeid(double));
}

static void test_equality_and_not_equal_operators()
{
    VectorM<3> v1(std::array<double, 3>{1.0, 2.0, 3.0});
    VectorM<3> v2{};

    assert(v1==v1);
    assert(v2==v2);
    assert(v1!=v2);
}

static void test_vector_addition()
{
    VectorM v1(std::array<double, 3>{1.0, 2.0, 3.0});
    VectorM<3> v2{};

    VectorM<3> v3 = v1 + v2;


    VectorM<3> v4 = v1 + v1;

    VectorM v5(std::array<double, 3>{2.0, 4.0, 6.0});

    assert(v1!=v2);
    assert(v2!=v3);
    assert(v1==v3);
    assert(v4==v5);
}



static void test_mutate_in_place_vector_addition()
{
    VectorM v1(std::array<double, 3>{1.0, 2.0, 3.0});
    VectorM<3> v2{};
    const VectorM v3(std::array<double, 3>{2.0, 4.0, 6.0});

    v1 += v2;
    assert(v1==v1);

    v2 += v2;
    assert(v2==v2);

    v1 += v1;
    assert(v1==v3);
}


static void test_inplace_vector_scalar_addition_overload()
{
    VectorM v1(std::array<double, 3>{1.0, 2.0, 3.0});

    const VectorM v2(std::array<double, 3>{2.0, 3.0, 4.0});

    const VectorM v3(std::array<double, 3>{0.0, 1.0, 2.0});

    v1 += 0;
    assert(v1==v1);

    v1 += 1;
    assert(v1==v2);

    v1 += -2.0;
    assert(v1==v3);
}


static void test_vector_scalar_addition_overload()
{
    VectorM v1(std::array<double, 3>{1.0, 2.0, 3.0});

    VectorM<3> v2 = v1 + 0.0;

    assert(v2==v1);

    VectorM<3> v3 = v1 + 1.0;
    const VectorM v4(std::array<double, 3>{2.0, 3.0, 4.0});

    assert(v3==v4);
}

int main()
{
    test_element_access();
    test_out_of_bounds_under();
    test_out_of_bounds_over();
    test_update_idx();
    test_len_method();
    test_default_constructor();
    test_convert_parameter_to_double_quiet();
    test_equality_and_not_equal_operators();
    test_vector_addition();
    test_mutate_in_place_vector_addition();
    test_inplace_vector_scalar_addition_overload();
    test_vector_scalar_addition_overload();
}
