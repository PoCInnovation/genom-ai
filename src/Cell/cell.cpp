#include "cell.hpp"
#include "genome.hpp"


Cell::Cell(const int x, const int y, const Genome& genome)
{
    this->alive = true;
    this->setPos(x, y);
    this->genome = genome;
    this->brain.setNeurons(this->genome.neurone_link_list);
    this->color = this->genome.getColor();
}

void Cell::setPos(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

Cell::~Cell()
= default;
