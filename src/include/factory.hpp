#ifndef FACTORY_H
#define FACTORY_H

#include <functional>

#include "Cell.hpp"
#include "brain.hpp"
#include "custom_random.hpp"

static std::vector<std::function<ICell *()>> cell_map = {
    []() {return new Cell(0, 0, Genome());}
};

class Factory {
public:
    static ICell *createRandomCell() {
        return cell_map[xorshift32() % cell_map.size()]();
    }
};

#endif //FACTORY_H
