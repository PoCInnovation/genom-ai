#include <iostream>
#include <fstream>
#include <vector>
#include <execution>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "die.hpp"
#include "reproduction.hpp"
#include "print_progress_bar.hpp"
#include "replay.hpp"

using namespace std;

static void compute_cells(Environnement &env, ICell *cell)
{
    const vector<float> inputs = {((static_cast<float>(cell->getXPos())/static_cast<float>(GRID_SIZE_X))-0.5f)*2.0f, ((static_cast<float>(cell->getYPos())/static_cast<float>(GRID_SIZE_Y))-0.5f)*2.0f, 1, 0, -1, 0.5, -0.5,
    env.get_crowd(cell, 0, -1), env.get_crowd(cell, 1, 0), env.get_crowd(cell, 0, 1), env.get_crowd(cell, -1, 0)};

    cell->forwardCell(inputs);
}

static void compute_cells_chunk(Environnement &env, const std::vector<ICell *>::iterator start, const std::vector<ICell *>::iterator end) {
    for (auto it = start; it != end; ++it) {
        compute_cells(env, *it);
    }
}

static void forward_cell(Environnement &env, ICell *cell) {
    const array<float, OUTPUT_SIZE> brain_output =  cell->getOutputs();

    env.move_cell(cell, static_cast<int>(brain_output[0]), static_cast<int>(brain_output[1]));
}

int compute_step(Environnement &env)
{
    std::vector<std::thread> threads;

    const auto begin = env.cell_list.begin();
    for (size_t i = 0; i < env.max_threads; ++i) {
        auto chunk_start = begin + i * env.chunk_size;
        auto chunk_end = (i == env.chunk_size - 1) ? env.cell_list.end() : chunk_start + env.chunk_size;

        threads.emplace_back(compute_cells_chunk, std::ref(env), chunk_start, chunk_end);
    }
    for (std::thread &thread : threads)
        thread.join();
    for (ICell *cell : env.cell_list)
        forward_cell(env, cell);
    return 0;
}

static int compute_gen(Environnement &env, sf::RenderWindow *window, const int gen)
{
    for (int j = 0; j < STEP_PER_GEN; j++){
        compute_step(env);
        if (gen >= GEN_TO_START_RENDER)
            render(env, window, gen);
    }
    return 0;
}

int loop(sf::RenderWindow *window)
{
    Environnement env = Environnement();

    for (int gen = 0; gen < MAX_GEN; gen++){
        if (gen == 0){
            for (int j = 0; j < CELL_COUNT; j++)
                env.create_cell_to_rand_pos();
        } else {
            if (gen % SAVE_EVERY_X_GEN == 0)
                save_gen(env);
            apply_die_rule(env);
            if (gen % 10 == 0)
                printf(" survival: %f\n", static_cast<float>(env.cell_list.size()) / static_cast<float>(CELL_COUNT));
            reproduce_cells(env);
        }
        if (gen == GEN_TO_START_RENDER && RENDER)
            window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
        compute_gen(env, window, gen);
        if (gen < GEN_TO_START_RENDER)
            print_progress_bar(static_cast<float>(gen)/static_cast<float>(GEN_TO_START_RENDER));
    }
    return 0;
}
