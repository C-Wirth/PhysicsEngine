cmake_minimum_required(VERSION 3.28.3)

project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Main entrypoint
add_executable(entry
        src/main.cc
        src/simulation/WorldSim.cc
)

target_include_directories(entry PRIVATE include)

# External Dependencies

#tomlplusplus
include(FetchContent)
FetchContent_Declare(
        tomlplusplus
        GIT_REPOSITORY https://github.com/marzer/tomlplusplus.git
        GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(tomlplusplus)

target_link_libraries(entry PRIVATE tomlplusplus::tomlplusplus)

# Test Library
include(CTest)
add_subdirectory(tests)
