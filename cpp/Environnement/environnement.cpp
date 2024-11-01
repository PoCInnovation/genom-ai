#include "environnement.hpp"
#include "simulation_parameters.hpp"
#include <vector>
#include <cell.hpp>
#include <random>

using namespace std;

Environnement::Environnement()
{
    this->map = vector(GRID_SIZE_Y, vector<Cell *>(GRID_SIZE_X, nullptr));
    this->cell_list = vector<Cell *>();
}

void Environnement::clear()
{
    for (int y = 0; y < GRID_SIZE_Y; y++)
        for (int x = 0; x < GRID_SIZE_X; x++)
            this->map[y][x] = nullptr;
    for (Cell* cell : this->cell_list)
        delete cell;
    this->cell_list.clear();
}

void Environnement::add_cell_to_rand_pos()
{
    Cell *cell;
    int x = rand() % GRID_SIZE_X;
    int y = rand() % GRID_SIZE_Y;

    while (this->map[y][x] != nullptr) {
        x = rand() % GRID_SIZE_X;
        y = rand() % GRID_SIZE_Y;
    }
    cell = new Cell(x, y);
    this->map[y][x] = cell;
    this->cell_list.push_back(cell);
}

bool Environnement::is_pos_free(int x, int y)
{
    if (x >= GRID_SIZE_X || x < 0 || y >= GRID_SIZE_Y || y < 0)
        return false;
    return this->map[y][x] == nullptr;
}

void Environnement::move_cell(Cell *cell, int x_offset, int y_offset)
{
    if (this->is_pos_free(cell->x + x_offset, cell->y + y_offset)) {
        this->map[cell->y + y_offset][cell->x + x_offset] = cell;
        this->map[cell->y][cell->x] = nullptr;
        cell->setPos(cell->x + x_offset, cell->y + y_offset);
    }
}

Environnement::~Environnement()
{
    for (auto& cellPtr : cell_list) {
        delete cellPtr;
        cellPtr = nullptr;
    }
}
