#include "cell.hpp"


Cell::Cell(int x, int y)
{
    this->setPos(x, y);
}

void Cell::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

Cell::~Cell()
{
}
