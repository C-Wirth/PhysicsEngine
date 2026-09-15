//
// Created by colby on 9/7/26.
//

#pragma once

#include <iomanip>
#include <ostream>
#include <vector>

#include "util/IndentStream.hpp"
#include "physics/particles/Particle2D.hpp"

constexpr double STEPS_PER_SECOND = 60.0;

struct WorldConfig{

        double timestep = 1.0 / STEPS_PER_SECOND; // Frequency

        std::vector<Particle2D> particles;

        explicit WorldConfig(std::vector<Particle2D> particles)
            : particles(std::move(particles))
        {
        }

};


inline auto print(std::ostream& stream, const WorldConfig& config, const std::size_t depth) -> std::ostream&
{
    stream << Indent(depth) << "WorldConfig: {\n";
    stream << Indent(depth + 1) << "timestep: 1.0 / "
            << std::fixed << std::setprecision(1) << STEPS_PER_SECOND << ",\n";
    stream << Indent(depth + 1) << "Particle 2D configs [\n";

    for (std::size_t i = 0 ; i < config.particles.size(); i++) {
        print(stream, config.particles[i], depth + 2, i);

        if (i != config.particles.size() -1)
        {
            stream << ",";
        }
        stream << "\n";
    }

    stream << Indent(depth + 1) << "]\n";
    stream << Indent(depth) << "}\n";
    return stream;
}

inline auto operator<<(std::ostream& stream, const WorldConfig& config) -> std::ostream&
{
    return print(stream, config, 0);
}