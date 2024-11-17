#include <vector>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "die.hpp"
#include "reproduction.hpp"
#include "print_progress_bar.hpp"

using namespace std;    

static void compute_cells(Environnement &env, Cell *cell)
{
    vector<float> inputs = {((((float)cell->x)/((float)GRID_SIZE_X))-0.5f)*2.0f, ((((float)cell->y)/((float)GRID_SIZE_Y))-0.5f)*2.0f, 1, 0, -1, 0.5, -0.5};
    array<float, OUTPUT_SIZE> brain_output;

    brain_output = env.brain.forward(inputs, cell->genome.neurone_link_list);

    env.move_cell(cell, brain_output[0], brain_output[1]);
    // if (brain_output[2] == 1)
    //     env.move_cell(cell, (rand() % 3)-1, (rand() % 3)-1);
}

static int compute_step(Environnement &env)
{
    for (Cell *cell : env.cell_list)
        compute_cells(env, cell);
    return 0;
}

static int compute_gen(Environnement &env, sf::RenderWindow *window, int gen)
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
            apply_die_rule(env);
            reproduce_cells(env);
        }
        if (gen == GEN_TO_START_RENDER)
            if (RENDER)
                window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
            else
                exit(0);
        compute_gen(env, window, gen);
        if (gen < GEN_TO_START_RENDER)
            print_progress_bar(((float)gen)/((float)GEN_TO_START_RENDER));
    }
    return 0;
}
