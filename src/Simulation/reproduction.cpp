#include <iostream>
#include <random>
#include <vector>
#include "simulation_parameters.hpp"
#include "ICell.hpp"
#include "environnement.hpp"
#include "genome.hpp"
#include "custom_random.hpp"
#include "factory.hpp"

using namespace std;

static bool doRandomCell()
{
    return (xorshift32() % 10000) <= RANDOM_NEW_CELL_CHANCE;
}

void linear_reproduce_cells(Environnement &env) {
    vector<ICell *> new_cells_list;
    std::array<Gene, GENOME_LENGTH> gen_list{};

    for (ICell *cell : env.cell_list) {
        new_cells_list.push_back(cell->reproduce());
    }
    while (new_cells_list.size() < CELL_COUNT) {
        if (doRandomCell()) {
            new_cells_list.push_back(Factory::createRandomCell());
        } else {
            new_cells_list.push_back(env.cell_list[xorshift32() % env.cell_list.size()]->reproduce());
        }
    }
    env.clear();
    for (ICell *ICell : new_cells_list)
        env.add_cell_to_rand_pos(ICell);
}

void random_reproduce_cells(Environnement &env)
{
    vector<ICell *> new_cell_list;
    ICell *cell;

    for (int i = 0; i < CELL_COUNT; i++){
        int index_parent_1 = xorshift32() % env.cell_list.size();
#if !ONE_PARENT
        int index_parent_2 = xorshift32() % env.cell_list.size();
        while (index_parent_2 == index_parent_1)
            index_parent_2 = xorshift32() % env.cell_list.size();
        cell = env.cell_list[index_parent_1]->reproduce(env.cell_list[index_parent_2]);
#else
        cell = env.cell_list[index_parent_1].reproduce();
#endif
        new_cell_list.push_back(cell);
    }
    env.clear();
    for (ICell *new_cell : new_cell_list)
        env.add_cell_to_rand_pos(new_cell);
}

void reproduce_cells(Environnement &env) {
#if RANDOM_REPRODUCE
    return random_reproduce_cells(env);
#else
    return linear_reproduce_cells(env);
#endif
}
