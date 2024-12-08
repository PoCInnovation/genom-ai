#ifndef CELL_HPP
#define CELL_HPP

#include "brain.hpp"
#include "genome.hpp"
#include "SFML/Graphics/Color.hpp"

class Cell
{
    public:
        int x{};
        int y{};
        Genome genome;
        Brain brain{};
        bool hasReproduce = false;
        sf::Color color{};


        Cell(int x, int y, const Genome& genome);
        void setPos(int x, int y);

        ~Cell();
};

#endif
