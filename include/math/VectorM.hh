#pragma once


#include <iostream>
#include <array>

template <std::size_t N>
class VectorM
{
public:
    /**
     * Default constructor, no initialized fields
     */
    explicit VectorM() = default;

    /**
     * Constructor when passed an array<N> v
     * @param v the templated underlying array of values
     */
    explicit VectorM(const std::array<double, N>& v)
        : a_(v)
    {
    }

    /**
     * Overloading operator[] to update a value in VectorM
     * @param idx
     * @return
     */
    auto operator[](std::size_t idx) -> double&
    {
        return a_.at(idx);
    }

    /**
     * Overloading operator[] to retrieve the value at an idx
     *
     * @param idx the
     * @return a reference to the updated value
     */
    auto operator[](std::size_t idx) const -> const double&
    {
        return a_.at(idx);
    }

    [[nodiscard]] auto len() const -> size_t
    {
        return size(a_);
    }


    /**
     *
     * @param o the other VectorM
     * @return bool True if the underlying arrays are equal
     */
    auto operator==(VectorM<N> o) -> bool
    {
        return a_ == o.a_;
    }


    /**
     *
     * @param o the other VectorM
     * @return bool True if the underlying arrays are not equal
     */
    auto operator!=(VectorM<N> o) -> bool
    {
        return a_ != o.a_;
    }

    /**
     * vector addition
     * @param o the other VectorM
     * @return a new VectorM
     */
    auto operator+(VectorM<N> o) -> VectorM
    {
        VectorM<N> v{};
        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] + o[idx];
        }
        return v;
    }

    /**
     * Mutate in place vector addition
     * @param o
     */
    auto operator+=(VectorM<N> o) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] += o[idx];
        }
    }


    /**
     * mutate-in-place vector-scalar addition
     * @param d the scalar
     */
    auto operator+=(double d) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] = (*this)[idx] + d;
        }
    }

    /**
     * creates a new Vector from vector-scalar addition
     * @param d the scalar
     * @return the new Vector
     */
    auto operator+(double d) -> VectorM
    {
        VectorM v{};
        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] + d;
        }
        return v;
    }


    /**
     * vector substraction
     * @param o the other VectorM
     * @return a new VectorM
     */
    auto operator-(VectorM o) -> VectorM
    {
        VectorM<N> v{};

        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] - o[idx];
        }
        return v;
    }


    /**
     * Mutate in place vector subtraction
     * @param o
     */
    auto operator-=(VectorM o) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] = (*this)[idx] - o[idx];
        }
    }


    /**
     * mutate-in-place vector-scalar subtraction
     * @param d the scalar
     */
    auto operator-=(double d) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] = (*this)[idx] - d;
        }
    }

    /**
     * mutate in place vector-scalar subtraction
     * @param d the scalar
     */
    auto operator-(double d) -> VectorM
    {
        VectorM<N> v{};
        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] - d;
        }
        return v;
    }

    /**
     * mutate in-place vector-scalar multiplication
     * @param d the scalar
     */
    auto operator*=(double d) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] = (*this)[idx] * d;
        }
    }

    /**
     * vector-scalar multiplication
     * @param d the scalar
     * @return the new Vector
     */
    auto operator*(double d) -> VectorM
    {
        VectorM<3> v{};
        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] * d;
        }
        return v;
    }

    /**
     * vector-scalar division
     * @param d the scalar
     * @return the new Vector
     */
    auto operator/(double d) -> VectorM
    {
        VectorM<3> v{};
        for (std::size_t idx = 0; idx < N; idx++)
        {
            v[idx] = (*this)[idx] / d;
        }
        return v;
    }

    /**
     * in-place vector-scalar division
     * @param d the scalar
     */
    auto operator/=(double d) -> void
    {
        for (std::size_t idx = 0; idx < N; idx++)
        {
            (*this)[idx] = (*this)[idx] / d;
        }
    }


    /**
     * vector dot product
     * @param v the other vector
     * @return the dot product of two vectors
     */
    auto dot(VectorM v) -> double
    {
        auto result = 0.0;

        for (std::size_t idx = 0; idx < N; idx++)
        {
            result += (*this)[idx] * v[idx];
        }
        return result;
    }

private:
    std::array<double, N> a_{};
};
