#include "math/VectorM.hh"
#include <array>

template <std::size_t N, std::size_t M>
class Matrix
{
public:
    /**
     * Matrix constructor for a row-major array
     */
    explicit Matrix(std::array<double, N * M> data)
        :
        data_(data),
        rows_(N),
        columns_(M)
    {
    }

    /**
     * Static Factory Identity method
     * Initialize an identity matrix with a
     */
    static Matrix Identity()
    {
        std::array<double, N * M> values{};
        for (std::size_t row = 0; row < N; row++)
        {
            for (std::size_t col = 0; col < M; col++)
            {
                if (row == col)
                {
                    values[(M * row) + col] = 1.0;
                }
                else
                {
                    values[(M * row) + col] = 0.0;
                }
            }
        }

        return Matrix(values);
    }

    /**
     * Static factory method
     * Initialize a Zero matrix
     */
    static Matrix Zero()
    {
        return Matrix(std::array<double, N * M>{});
    }

    /**
     * Static factory method
     * Initialize a Ones matrix
     */
    static Matrix Ones()
    {
        return Matrix(std::array<double, N * M>{
            []
            {
                std::array<double, N * M> a;
                a.fill(1.0);
                return a;
            }()
        });
    }

    /**
     * rows attribute
     * @return
     */
    [[nodiscard]] auto rows() const -> std::size_t
    {
        return rows_;
    }

    /**
     * columns attribute
     * @return
     */
    [[nodiscard]] auto columns() const -> std::size_t
    {
        return columns_;
    }

    /**
     * element mutator
     * @param row the row idx
     * @param col the column idx
     * @return the value at [row,col]
     */
    double& operator[](const std::size_t row, const std::size_t col)
    {
        return data_[row * M + col];
    }


    /**
     * element accessor
     * @param row
     * @param col
     */
    const double& operator[](const std::size_t row, const std::size_t col) const
    {
        return data_[row * M + col];
    }


    /**
     * Matrix-Vector multiplication
     * @param v the input vector
     * @return the transformed vector
     */
    auto operator*(const VectorM<M>& v) const -> VectorM<N>
    {
        auto result = VectorM<N>{};
        for (std::size_t i = 0; i < N; i++)
            for (std::size_t j = 0; j < M; j++)
                result[i] += (*this)[i,j] * v[j];
        return result;
    }

    /**
     *  Matrix-scalar multiplication
     * @param scalar
     * @return the scaled matrix
     */
    auto operator*(const double scalar) const -> Matrix
    {
        Matrix<N, M> result = Matrix<N, M>::Zero();
        for (std::size_t i = 0; i < N; i++)
            for (std::size_t j = 0; j < M; j++)
                result[i,j] = scalar * (*this)[i,j];
        return result;
    }

    /**
     * matrix multiplication
     * @param o other matrix
     * @return new matrix
     */
    template <std::size_t O>
    auto matMul(const Matrix<M, O>& o) const -> Matrix<N, O>
    {
        Matrix<N, O> result = Matrix<N, O>::Zero();

        for (std::size_t i = 0; i < N; i++)
            for (std::size_t j = 0; j < O; j++)
                for (std::size_t k = 0; k < M; k++)
                    result[i,j] += (*this)[i,k] * o[k,j];
        return result;
    }


    /**
     * Matrix Transpose Operations
     * @return
     */
    auto T() -> Matrix<M, N>
    {
        Matrix<M, N> result = Matrix<M, N>::Zero();
        // columns
        for (std::size_t j = 0; j < M; j++)
        {
            // rows
            for (std::size_t i = 0; i < N; i++)
            {
                result[j,i] = (*this)[i,j];
            }
        }
        return result;
    }

private:
    // the underlying row-major array for storing the matrix
    std::array<double, N * M> data_{};
    std::size_t rows_ = 0;
    std::size_t columns_ = 0;
};
