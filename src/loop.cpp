#include <vector>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "die.hpp"
#include "reproduction.hpp"

using namespace std;    

static void compute_cells(Environnement &env, Cell *cell)
{
    env.move_cell(cell, cell->x_speed, cell->y_speed);
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
        compute_gen(env, window, gen);
    }
    return 0;
}
