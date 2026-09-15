//
// Created by colby on 9/6/26.
//

#pragma once

#include <simulation/WorldConfig.hpp>


class WorldSim
{
public:
    explicit WorldSim(const WorldConfig& config);

    [[nodiscard]] auto GetConfig() const -> WorldConfig;

private:
    double timestep_;
};
