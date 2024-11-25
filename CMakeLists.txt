cmake_minimum_required(VERSION 3.27)
project(genomAI LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(genomAI
    src/Brain/brain.cpp
    src/Cell/cell.cpp
    src/Environnement/environnement.cpp
    src/Genome/genome.cpp
    src/Neurone/neuron.cpp
    src/Neurone/neuron_link.cpp
    src/Renderer/render.cpp
    src/Simulation/die.cpp
    src/Simulation/reproduction.cpp
    src/custom_random.cpp
    src/loop.cpp
    src/main.cpp
    src/print_progress_bar.cpp
    src/include/brain.hpp
    src/include/cell.hpp
    src/include/die.hpp
    src/include/environnement.hpp
    src/include/genome.hpp
    src/include/loop.hpp
    src/include/neuron.hpp
    src/include/neuron_link.hpp
    src/include/render.hpp
    src/include/reproduction.hpp
    src/include/simulation_parameters.hpp
    src/include/print_progress_bar.hpp
    src/include/custom_random.hpp
)

include_directories(src/include)

target_link_libraries(genomAI PRIVATE sfml-graphics)
target_compile_features(genomAI PRIVATE cxx_std_17)
