#include <array>
#include <cassert>
#include <stdexcept>
#include <exception>
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
 * tests the default constructor
 */
static void test_default_constructor()
{
    VectorM<2> v{};
    // TODO: check for length
    assert(v[0] == 0 && v[1] == 0);

    v[0] = 1.0;
    assert(v[0] == 1.0);

    v[1] = 2.0;
    assert(v[1] == 2.0);


}
int main()
{
    test_element_access();
    test_out_of_bounds_under();
    test_out_of_bounds_over();
    test_update_idx();
    test_default_constructor();
}
