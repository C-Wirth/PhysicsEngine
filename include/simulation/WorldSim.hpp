#pragma once

#include <vector>

#include "physics/particles/Entity.hpp"
#include "simulation/WorldConfig.hpp"


class WorldSim
{
public:
    explicit WorldSim(WorldConfig config);

    [[nodiscard]] auto GetConfig() const -> const WorldConfig& { return config_; }
    auto WorldSimStep() -> void;

private:
    WorldConfig config_;
};
