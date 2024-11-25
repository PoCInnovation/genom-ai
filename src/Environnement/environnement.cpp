#include <vector>
#include <cell.hpp>
#include <random>
#include "environnement.hpp"
#include "simulation_parameters.hpp"
#include "genome.hpp"
#include "brain.hpp"
#include "custom_random.hpp"

using namespace std;

Environnement::Environnement()
{
    this->map = vector<Cell *>(GRID_SIZE_X * GRID_SIZE_Y, nullptr);
    this->cell_list = vector<Cell *>();
}

void Environnement::clear()
{
    for (int y = 0; y < GRID_SIZE_Y; y++)
        for (int x = 0; x < GRID_SIZE_X; x++)
            SET_CELL(nullptr, x, y);
    for (Cell* cell : this->cell_list)
        delete cell;
    this->cell_list.clear();
}

void Environnement::create_cell_to_rand_pos()
{
    Cell *cell;
    int x = xorshift32() % GRID_SIZE_X;
    int y = xorshift32() % GRID_SIZE_Y;

    while (GET_CELL(x, y) != nullptr) {
        x = xorshift32() % GRID_SIZE_X;
        y = xorshift32() % GRID_SIZE_Y;
    }
    cell = new Cell(x, y, Genome());
    SET_CELL(cell, x, y);
    this->cell_list.push_back(cell);
}

void Environnement::add_cell_to_rand_pos(Cell *cell)
{
    int x = xorshift32() % GRID_SIZE_X;
    int y = xorshift32() % GRID_SIZE_Y;

    while (GET_CELL(x, y) != nullptr) {
        x = xorshift32() % GRID_SIZE_X;
        y = xorshift32() % GRID_SIZE_Y;
    }
    SET_CELL(cell, x, y);
    cell->setPos(x, y);
    this->cell_list.push_back(cell);
}

bool Environnement::is_pos_free(int x, int y)
{
    if (x >= GRID_SIZE_X || x < 0 || y >= GRID_SIZE_Y || y < 0)
        return false;
    return GET_CELL(x, y) == nullptr;
}

void Environnement::move_cell(Cell *cell, int x_offset, int y_offset)
{
    if (this->is_pos_free(cell->x + x_offset, cell->y)) {
        SET_CELL(cell, cell->x + x_offset, cell->y);
        SET_CELL(nullptr, cell->x, cell->y);
        cell->setPos(cell->x + x_offset, cell->y);
    }
    if (this->is_pos_free(cell->x, cell->y + y_offset)) {
        SET_CELL(cell, cell->x, cell->y + y_offset);
        SET_CELL(nullptr, cell->x, cell->y);
        cell->setPos(cell->x, cell->y + y_offset);
    }
}

Environnement::~Environnement()
{
    for (Cell *cellPtr : cell_list) {
        delete cellPtr;
        cellPtr = nullptr;
    }
}
