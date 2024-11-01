#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
    public:
        Cell(int x, int y);
        void setPos(int x, int y);
        ~Cell();
        int x;
        int y;
};

#endif
