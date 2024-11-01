#include <vector>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"

using namespace std;

void add_cell_to_rand_pos(vector<vector<Cell *>> &cell_list)
{
    int x = rand() % GRID_SIZE_X;
    int y = rand() % GRID_SIZE_Y;
    while (cell_list[y][x] != 0) {
        x = rand() % GRID_SIZE_X;
        y = rand() % GRID_SIZE_Y;
    }
    cell_list[y][x] = new Cell(x, y);
}

void clear_map(vector<vector<Cell *>> &cell_list)
{
    for (vector<Cell *> &line : cell_list)
        line.assign(GRID_SIZE_X, nullptr);
}

bool pos_is_free(vector<vector<Cell *>> &cell_list, int x, int y)
{
    if (x >= GRID_SIZE_X || x < 0 || y >= GRID_SIZE_Y || y < 0)
        return false;
    if (cell_list[y][x] != 0)
        return false;
    return true;
}

void compute_cells(vector<vector<Cell *>> &cell_list, Cell *cell)
{
    if (pos_is_free(cell_list, cell->x-1, cell->y)) {
        cell_list[cell->y][cell->x-1] = cell_list[cell->y][cell->x];
        cell_list[cell->y][cell->x] = nullptr;
        cell->setPos(cell->x-1, cell->y);
    }
}

int compute_step(vector<vector<Cell *>> &cell_list)
{
    for (vector<Cell *> &line : cell_list)
        for (Cell *cell : line)
            if (cell != 0)
                compute_cells(cell_list, cell);
    return 0;
}

int compute_gen(vector<vector<Cell *>> &cell_list, sf::RenderWindow *window)
{
    for (int j = 0; j < STEP_PER_GEN; j++){
        compute_step(cell_list);
        render(cell_list, window);
    }
    return 0;
}

int loop(sf::RenderWindow *window)
{
    vector<vector<Cell *>> cell_list(GRID_SIZE_Y, vector<Cell *>(GRID_SIZE_X, nullptr));

    for (int i = 0; i < MAX_GEN; i++){
        clear_map(cell_list);
        for (int j = 0; j < CELL_COUNT; j++)
            add_cell_to_rand_pos(cell_list);
        compute_gen(cell_list, window);
    }
    return 0;
}
