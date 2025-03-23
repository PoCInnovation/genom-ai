#ifndef CELL_HPP
#define CELL_HPP

#include "brain.hpp"
#include "genome.hpp"
#include "Interfaces/icell.hpp"
#include "SFML/Graphics/Color.hpp"

class Cell : virtual public ICell
{
        int x{};
        int y{};
        Genome genome;
        IBrain *brain;
        bool hasReproduce = false;
        sf::Color color{};

    public:
        Cell(int x, int y, const Genome& genome);
        void setPos(int x, int y) override;
        int getXPos() const override {return x;}
        int getYPos() const override {return y;}
        sf::Color getColor() const override {return color;}
        ~Cell() override;
        ICell *reproduce() override;
        ICell *reproduce(ICell *other) override;
        std::array<float, OUTPUT_SIZE> getOutputs() const override;
        void forwardCell(std::vector<float> inputList) override;
};

#endif
