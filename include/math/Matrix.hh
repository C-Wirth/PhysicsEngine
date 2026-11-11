#include <array>

template <std::size_t N, std::size_t M>
class Matrix
{
public:
    /**
     * Standard consturctor
     *
     */
    explicit Matrix(std::array<double, N * M> data)
        :
        data_(data)
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
     * Initialize an identity matrix with a static method
     */
    static Matrix Zero()
    {
    }

    const double& operator[](const std::size_t row, const std::size_t col)
    {
        return data_[row * M + col];
    }

private:
    // the underlying row-major array for storing the matrix
    std::array<double, N * M> data_{};
};
