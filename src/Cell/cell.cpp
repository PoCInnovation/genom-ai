#include "cell.hpp"
#include "genome.hpp"


Cell::Cell(int x, int y, Genome genome)
{
    this->setPos(x, y);
    this->x_speed = 0;
    this->y_speed = 0;
    this->genome = genome;
    this->brain.setNeurons(this->genome.neurone_link_list);
}

void Cell::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void Cell::setSpeed(int x_speed, int y_speed)
{
    this->x_speed = x_speed;
    this->y_speed = y_speed;
}

Cell::~Cell()
= default;
