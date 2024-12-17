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
    this->food_bar = array<float, CELL_COUNT>();
    this->water_bar = array<float, CELL_COUNT>();
    this->obstacle_list = vector<bool>();

    this->food_bar.fill(0.0f);
    this->water_bar.fill(0.0f);
    this->obstacle_list.assign(GRID_SIZE_X * GRID_SIZE_Y, false);
    // this->draw_obstacle_square(15, 0, 2, 50);
    // this->draw_obstacle_square(25, 50, 2, 50);
}

void Environnement::draw_obstacle_square(int x, int y, int w, int h)
{
    for (int i = 0; i < w * h; i++)
        this->obstacle_list[((y+((int)i/w))*GRID_SIZE_X)+(i%w)+x] = true;
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

    while (!this->is_pos_free(x, y)) {
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

    while (!this->is_pos_free(x, y)) {
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
    if (this->obstacle_list[y*GRID_SIZE_X+x])
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

float Environnement::get_crowd(Cell *cell, int x_offset, int y_offset, int distance /* default = 3 */)
{
    float crowd = 0;

    for (int i = 1; i < distance + 1; i++)
        if (!this->is_pos_free(cell->x + x_offset * i, cell->y + y_offset * i))
            crowd++;
    return crowd / distance;
}

Environnement::~Environnement()
{
    for (Cell *cellPtr : cell_list) {
        delete cellPtr;
        cellPtr = nullptr;
    }
}
