#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include "simulation_parameters.hpp"
#include "cell.hpp"
#define GET_ENV_CELL(env, x, y) (env)->map[(y)*GRID_SIZE_X+(x)]
#define SET_ENV_CELL(env, cell, x, y) (env)->map[(y)*GRID_SIZE_X+(x)] = (cell)
#define GET_CELL(x, y) GET_ENV_CELL(this, (x), (y))
#define SET_CELL(cell, x, y) SET_ENV_CELL(this, (cell), (x), (y))

class Environnement
{  
    public:
        std::vector<Cell *> map;
        std::vector<Cell *> cell_list;

        Environnement();
        void clear();
        void create_cell_to_rand_pos();
        void add_cell_to_rand_pos(Cell *);
        bool is_pos_free(int x, int y);
        void move_cell(Cell *, int x_offset, int y_offset);
        ~Environnement();
};

#endif
