#pragma once


#include <array>

template <std::size_t N>
class VectorM
{
public:

    /**
     * Default constructor, no initialized fields
     */
    explicit VectorM()= default;

    /**
     * Constructor when passed an array<N> v
     * @param v the templated underlying array of values
     */
    explicit VectorM(const std::array<double, N>& v)
        : v_(v)
    {
    }

    /**
     * Overloading operator[] to update a value in VectorM
     * @param idx
     * @return
     */
    auto operator[](std::size_t idx) -> double&
    {
        return v_.at(idx);
    }

    /**
     * Overloading operator[] to retrieve the value at an idx
     *
     * @param idx the
     * @return a reference to the updated value
     */
    auto operator[](std::size_t idx) const -> const double&
    {
        return v_.at(idx);
    }

private:
    std::array<double, N> v_{};
};
