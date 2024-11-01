#include <vector>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"

using namespace std;    

static void clear_map(vector<vector<Cell *>> &cell_list)
{
    for (vector<Cell *> &line : cell_list)
        line.assign(GRID_SIZE_X, nullptr);
}

static bool pos_is_free(vector<vector<Cell *>> &cell_list, int x, int y)
{
    if (x >= GRID_SIZE_X || x < 0 || y >= GRID_SIZE_Y || y < 0)
        return false;
    if (cell_list[y][x] != 0)
        return false;
    return true;
}

static void compute_cells(Environnement &env, Cell *cell)
{
    env.move_cell(cell, -1, 0);
}

static int compute_step(Environnement &env)
{
    for (Cell *cell : env.cell_list)
        compute_cells(env, cell);
    return 0;
}

static int compute_gen(Environnement &env, sf::RenderWindow *window)
{
    for (int j = 0; j < STEP_PER_GEN; j++){
        compute_step(env);
        render(env, window);
    }
    return 0;
}

int loop(sf::RenderWindow *window)
{
    Environnement env = Environnement();

    for (int i = 0; i < MAX_GEN; i++){
        env.clear();
        for (int j = 0; j < CELL_COUNT; j++)
            env.add_cell_to_rand_pos();
        compute_gen(env, window);
    }
    return 0;
}
