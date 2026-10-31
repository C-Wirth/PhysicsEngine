#include <iostream>

#include "simulation/WorldSim.hh"
#include <toml++/toml.hpp>

auto main() -> int
{
    const WorldSim world_sim;

    std::cout<< world_sim << "\n";

}
