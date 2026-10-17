cmake_minimum_required(VERSION 3.28.3)

project(PhysicsEngine)

# Main entrypoint
add_executable(Entry
        src/main.cc
)

target_include_directories(Entry PRIVATE include)


# Test Library
include(CTest)

add_subdirectory(tests)