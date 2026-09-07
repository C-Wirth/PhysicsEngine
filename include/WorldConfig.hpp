//
// Created by colby on 9/7/26.
//

#pragma once

#include <iomanip>
#include <ostream>

constexpr double STEPS_PER_SECOND = 60.0;

struct WorldConfig{

    double timestep = 1.0 / STEPS_PER_SECOND; // Frequency
};

inline auto operator<< (std::ostream& stream, const WorldConfig& config) -> std::ostream&
{
    stream << "WorldConfig: { "
        << "timestep: " << "1.0 / " << std::fixed << std::setprecision(1) << STEPS_PER_SECOND
        << " } ";

    return stream;
}


