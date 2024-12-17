#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include "cell.hpp"
#include "brain.hpp"
#define GET_ENV_CELL(env, x, y) (env)->map[(y)*GRID_SIZE_X+(x)]
#define SET_ENV_CELL(env, cell, x, y) (env)->map[(y)*GRID_SIZE_X+(x)] = (cell)
#define GET_CELL(x, y) GET_ENV_CELL(this, (x), (y))
#define SET_CELL(cell, x, y) SET_ENV_CELL(this, (cell), (x), (y))

class Environnement
{  
    public:
        std::vector<Cell *> map;
        std::vector<Cell *> cell_list;
        std::vector<bool> obstacle_list;
        std::array<float, CELL_COUNT> food_bar;
        std::array<float, CELL_COUNT> water_bar;

        Environnement();
        void clear();
        void create_cell_to_rand_pos();
        void draw_obstacle_square(int x, int y, int w, int h);
        void add_cell_to_rand_pos(Cell *);
        bool is_pos_free(int x, int y);
        void move_cell(Cell *, int x_offset, int y_offset);
        float get_crowd(Cell *cell, int x_offset, int y_offset, int distance = 3);
        ~Environnement();
};

#endif
