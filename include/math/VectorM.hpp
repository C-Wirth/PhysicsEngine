#pragma once

#include <array>
#include <ostream>
#include "util/IndentStream.hpp"

/**
 * @brief Fixed-size mathematical vector.
 *
 * Represents an N-dimensional vector whose components are stored
 * as double-precision floating-point values.
 *
 * @tparam N Number of components in the vector.
 */
template <std::size_t N>
class VectorM
{
public:
    /**
     * @brief Constructs a vector from an array of components.
     *
     * @param components Initial vector components.
     */
    explicit VectorM(std::array<double, N> components) : components_(components) {}


    /**
     * @brief Constructs an empty VectorM
     */
    VectorM() : components_{} {}

    auto operator[](std::size_t i) -> double&;
    auto operator[](std::size_t i) const -> const double&;

private:
    std::array<double, N> components_;
};

template <std::size_t N>
auto VectorM<N>::operator[](std::size_t i) -> double&
{
    return components_[i];
}

template <std::size_t N>
auto VectorM<N>::operator[](std::size_t i) const -> const double&
{
    return components_[i];

}
/**
 * @brief Adds two vectors component-wise.
 *
 * @tparam N Number of components in the vectors.
 * @param l Left-hand vector.
 * @param r Right-hand vector.
 * @return The component-wise sum of the two vectors.
 */
template <std::size_t N>
auto operator+(const VectorM<N>& l,
               const VectorM<N>& r) -> VectorM<N>
{
    VectorM<N> result;
    for (std::size_t i = 0 ; i < N ; i++)
    {
        result[i] = l[i] + r[i];
    }

    return result;
}


/**
 *
 * @tparam N Number of components in the vectors.
 * @param l Left-hand vector.
 * @param r Right-hand vector.
 * @return The '+' operator of the two vectors
 */
template <std::size_t N>
auto operator+=(VectorM<N>& l, const VectorM<N>& r) -> VectorM<N>&
{
    l = l + r;
    return l;
}

/**
 * @brief Adds two vectors component-wise.
 *
 * @tparam N Number of components in the vectors.
 * @param l Left-hand vector.
 * @param r Right-hand vector.
 * @return The component-wise difference of the two vectors.
 */
template <std::size_t N>
auto operator-(const VectorM<N>& l,
               const VectorM<N>& r) -> VectorM<N>
{
    VectorM<N> result;
    for (std::size_t i = 0; i < N; i++)
    {
        result[i] = l[i] - r[i];
    }

    return result;
}

/**
 * @brief Vector-scalar multiplication
 * @tparam N Number of components in the vector
 * @param v the vector
 * @param scalar the scalar, a double
 * @return the new vector
 */
template <std::size_t N>
auto operator*(const VectorM<N>& v,
               double scalar) -> VectorM<N>
{
    VectorM<N> result;
    for(std::size_t i = 0 ; i < N ; i++)
    {
        result[i] = v[i] * scalar;
    }

    return result;
}


/**
 * @brief Vector-scalar division
 * @tparam N Number of components in the vector
 * @param v the vector
 * @param scalar the scalar, a double
 * @return the new vector
 */
template <std::size_t N>
auto operator/(const VectorM<N>& v,
               double scalar) -> VectorM<N>
{
    VectorM<N> result;
    for(std::size_t i = 0 ; i < N ; i++)
    {
        result[i] = v[i] / scalar;
    }

    return result;
}

/**
 * @brief dot product between two vectors
 *
 * @tparam N Number of components in the vectors.
 * @param l Left-hand vector.
 * @param r Right-hand vector.
 * @return the dot product of the two vectors, a double
 */
template<std::size_t N>
auto dot(VectorM<N> l, VectorM<N> r) -> double
{
    double result=0;
    for(std::size_t i=0 ; i < N ; i++)
    {
        result+= l[i]*r[i];
    }
    return result;
}

template<std::size_t N>
auto print(std::ostream& stream, VectorM<N> v, const size_t depth) -> std::ostream&
{
    stream << Indent(depth) << "(";
    for (std::size_t i = 0 ; i < N ; i++)
    {

        stream << v[i];
        if (i != N-1)
        {
            stream << ",";
        }
    }
    stream << ")";
    return stream;
}


template<std::size_t N>
 auto operator<<(std::ostream& stream, const VectorM<N>& v) -> std::ostream&
{
    return print(stream, v, 0);
}