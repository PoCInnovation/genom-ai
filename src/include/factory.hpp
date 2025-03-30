#ifndef FACTORY_H
#define FACTORY_H

#include <functional>

#include "Cell.hpp"
#include "brain.hpp"
#include "custom_random.hpp"

static const std::vector<std::function<ICell *(Genome)>> cell_map = {
    [](const Genome &gen) {return new Cell(0, 0, gen);}
};

static const std::vector<std::function<IBrain *()>> brain_map = {
    []() {return new Brain();}
};

class Factory {
public:
    static ICell *createRandomCell() {
        return cell_map[xorshift32() % cell_map.size()](Genome());
    }
    static ICell *createRandomCell(const Genome& genome) {
        return cell_map[xorshift32() % cell_map.size()](genome);
    }
    static IBrain *createBrain() {
        return brain_map[xorshift32() % brain_map.size()]();
    }
};

#endif //FACTORY_H
