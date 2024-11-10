#ifndef ENVIRONNEMENT_HPP
#define ENVIRONNEMENT_HPP

#include <vector>
#include "cell.hpp"

class Environnement
{  
    public:
        std::vector<std::vector<Cell *>> map;
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
