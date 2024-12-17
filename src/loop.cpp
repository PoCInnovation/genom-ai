#include <iostream>
#include <fstream>
#include <vector>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "die.hpp"
#include "reproduction.hpp"
#include "print_progress_bar.hpp"
#include "replay.hpp"

using namespace std;

static void compute_cells(Environnement &env, Cell *cell, int cell_index)
{
    const vector<float> inputs = {((static_cast<float>(cell->x)/static_cast<float>(GRID_SIZE_X))-0.5f)*2.0f, ((static_cast<float>(cell->y)/static_cast<float>(GRID_SIZE_Y))-0.5f)*2.0f, 1, 0, -1, 0.5, -0.5,
    env.get_crowd(cell, 0, -1), env.get_crowd(cell, 1, 0), env.get_crowd(cell, 0, 1), env.get_crowd(cell, -1, 0), env.food_bar[cell_index], env.water_bar[cell_index]};

    const array<float, OUTPUT_SIZE> brain_output = cell->brain.forward_cell(inputs);

    env.move_cell(cell, static_cast<int>(brain_output[0]), static_cast<int>(brain_output[1]));
}

int compute_step(Environnement &env, int gen)
{
    for (int i = 0; i < CELL_COUNT; ++i){
        env.food_bar[i] -= min(0.01, 0.003 + 0.001 * (gen/50));
        env.water_bar[i] -= min(0.01, 0.003 + 0.001 * (gen/50));
        if (env.cell_list[i]->x < GRID_SIZE_X*0.45)
            env.food_bar[i] = min(1.0, env.food_bar[i] + 0.5);
        if (env.cell_list[i]->x > GRID_SIZE_X*0.55)
            env.water_bar[i] = min(1.0, env.water_bar[i] + 0.5);
        if (env.food_bar[i] <= 0 || env.water_bar[i] <= 0)
            env.cell_list[i]->alive = false;
        compute_cells(env, env.cell_list[i], i);
    }
    return 0;
}

static int compute_gen(Environnement &env, sf::RenderWindow *window, int gen)
{
    for (int j = 0; j < STEP_PER_GEN; j++){
        compute_step(env, gen);
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
                printf(" survival: %f\n", (float)env.cell_list.size() / (float)CELL_COUNT);
            reproduce_cells(env);
        }
        env.food_bar.fill(1.0f);
        env.water_bar.fill(1.0f);
        if (gen == GEN_TO_START_RENDER && RENDER)
            window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
        compute_gen(env, window, gen);
        if (gen < GEN_TO_START_RENDER)
            print_progress_bar(((float)gen)/((float)GEN_TO_START_RENDER));
    }
    return 0;
}
