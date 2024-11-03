#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
    public:
        int x;
        int y;
        int x_speed;
        int y_speed;
        
        Cell(int x, int y);
        void setPos(int x, int y);
        void setSpeed(int x_speed, int y_speed);
        ~Cell();
};

#endif
