cmake_minimum_required(VERSION 3.28)
project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_CLANG_TIDY clang-tidy-23)

include(FetchContent)

add_library(PhysicsEngine
        SHARED
        src/simulation/WorldSim.cc
)

target_include_directories(PhysicsEngine
        PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(
        Entry
        examples/Entry.cc
)

target_link_libraries(Entry PRIVATE PhysicsEngine)


# DOCTEST import
set(DOCTEST_VERSION v2.4.11)
FetchContent_Declare(
        doctest
        URL  https://raw.githubusercontent.com/doctest/doctest/${DOCTEST_VERSION}/doctest/doctest.h
        DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(doctest)

set(DOCTEST_INCLUDE_DIR ${doctest_SOURCE_DIR})

include_directories(${DOCTEST_INCLUDE_DIR})