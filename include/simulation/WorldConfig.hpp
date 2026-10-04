#pragma once

#include <iomanip>
#include <memory>
#include <ostream>
#include <vector>
#include <ranges>

#include "util/IndentStream.hpp"
#include "physics/particles/Entity.hpp"

constexpr double STEPS_PER_SECOND = 60.0;

struct WorldConfig{

        double timestep = 1.0 / STEPS_PER_SECOND; // Frequency
        std::vector<std::unique_ptr<Entity<2>>> entities;

        explicit WorldConfig(std::vector<std::unique_ptr<Entity<2>>> entities)
            : entities(std::move(entities))
        {
        }

};


inline auto print(std::ostream& stream, const WorldConfig& config, const std::size_t depth) -> std::ostream&
{
    stream << Indent(depth) << "WorldConfig: {\n";
    stream << Indent(depth + 1) << "timestep: 1.0 / "
            << std::fixed << std::setprecision(1) << STEPS_PER_SECOND << ",\n";
    stream << Indent(depth + 1) << "Particle configs [\n";

    for (std::size_t i = 0 ; i < config.entities.size(); i++) {
        config.entities[i]->print(stream, depth + 2);

        if (i != config.entities.size() -1)
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