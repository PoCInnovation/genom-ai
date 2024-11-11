#ifndef CELL_HPP
#define CELL_HPP

#include "genome.hpp"

class Cell
{
    public:
        int x;
        int y;
        int x_speed;
        int y_speed;
        Genome genome;
        
        Cell(int x, int y, Genome genome);
        void setPos(int x, int y);
        void setSpeed(int x_speed, int y_speed);
        ~Cell();
};

#endif
