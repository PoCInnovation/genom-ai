#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
    public:
        int x;
        int y;
        
        Cell(int x, int y);
        void setPos(int x, int y);
        ~Cell();
};

#endif
