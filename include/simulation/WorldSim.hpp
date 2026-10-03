#pragma once

#include <vector>

#include "simulation/WorldConfig.hpp"

class WorldSim
{
public:
    explicit WorldSim(WorldConfig config);

    [[nodiscard]] auto GetConfig() const -> const WorldConfig& { return config_; }
    auto WorldSimStep() -> void;

private:
    const WorldConfig config_;
};
