#pragma once

#include <vector>

#include "simulation/WorldConfig.hpp"

class WorldSim
{
public:

    explicit WorldSim(const WorldConfig& config);

    [[nodiscard]] auto GetConfig() const -> WorldConfig;

    auto Step() -> void;


private:
    double timestep_;
};
