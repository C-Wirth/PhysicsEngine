#pragma once

#include <ostream>
struct Geometry2D
{
    // for now, our objects will just be rectangles
    explicit Geometry2D(
    const double width,
    const double height
    ) : width_(width),
        height_(height)
    {

    }

    [[nodiscard]] auto width() const -> double
    {
        return width_;
    }

    [[nodiscard]] auto height() const -> double
    {
        return height_;
    }

private:
    double width_;
    double height_;
};

inline auto operator<< (std::ostream& stream, const Geometry2D& geometry) -> std::ostream&
{
    stream << "Geometry2D: {\n"
        << "\n\twidth: " << std::fixed << std::setprecision(4) << geometry.width()
        << "\n\theight: " << std::fixed << std::setprecision(4) << geometry.height()
        << "\n}";
    return stream;
}


