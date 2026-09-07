#include "WorldSim.hpp"
#include  "WorldConfig.hpp"

#include <iostream>

auto main() -> int
{
    constexpr WorldConfig config;
    std::cout << config << "\n";

    WorldSim world(config);


    return 0;
}
