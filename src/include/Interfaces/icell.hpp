#ifndef ICELL_H
#define ICELL_H

#include <SFML/Graphics/Color.hpp>
#include "neuron_link.hpp"
#include <array>
#include "genome.hpp"

class ICell {
    public:
        virtual void setPos(int x, int y) = 0;
        virtual int getXPos() const = 0;
        virtual int getYPos() const = 0;
        virtual const Genome &getGenome() const = 0;
        virtual sf::Color getColor() const = 0;
        virtual ICell *reproduce() = 0;
        virtual ICell *reproduce(ICell *other) = 0;
        virtual ~ICell() = default;
        virtual std::array<float, OUTPUT_SIZE> getOutputs() const = 0;
        virtual void forwardCell(std::vector<float> inputList) = 0;
};

#endif //ICELL_H
