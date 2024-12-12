#include <iostream>
#include <random>
#include <vector>
#include "simulation_parameters.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "genome.hpp"
#include "custom_random.hpp" 

using namespace std;

static bool mutation_happen()
{
    return (xorshift32() % 10000) <= MUTATION_CHANCE;
}

static bool doRandomCell()
{
    return (rand() % 10000) <= RANDOM_NEW_CELL_CHANCE;
}

static Gene get_gene(int link_index, const Cell *parent1, const Cell *parent2)
{
    int rand_number = xorshift32();

    if (rand_number % 2 == 0)
        return parent1->genome.gen_list[link_index];
    else
        return parent2->genome.gen_list[link_index];
}

static void mutate(Gene &gen)
{
    const int index = xorshift32() % GEN_LENGTH;

    gen[index] = !gen[index];
}

static std::array<Gene, GENOME_LENGHT> inherit_genes(const Cell *parent1, Cell *parent2)
{
    std::array<Gene, GENOME_LENGTH> gen_list{};

    for (int i = 0; i < GENOME_LENGTH; i++){
#if ONE_PARENT == true
        gen_list[i] = parent1->genome.gen_list[i];
#else
        gen_list[i] = get_gene(i, parent1, parent2);
#endif
        if (mutation_happen())
            mutate(gen_list[i]);
    }
    return gen_list;
}

// static void inherit_genes(Cell *child_cell, Cell *parent1, Cell *parent2)
// {
//     // use each bit of the rand number to save computation power
//     int rand_number = rand();
//     int child_x_speed = (((rand_number >> 0) % 2) == 0) ? (parent1->x_speed) : (parent2->x_speed);
//     int child_y_speed = (((rand_number >> 1) % 2) == 0) ? (parent1->y_speed) : (parent2->y_speed);

//     if (mutation_happen())
//         child_x_speed += (((rand_number >> 2) % 2) == 0) ? 1 : -1;
//     if (mutation_happen())
//         child_y_speed += (((rand_number >> 3) % 2) == 0) ? 1 : -1;
//     child_cell->setSpeed(child_x_speed, child_y_speed);
// }

void linear_reproduce_cells(Environnement &env) {
    vector<Cell *> new_cells_list;
    std::array<Gene, GENOME_LENGHT> gen_list{};

    for (const Cell *cell : env.cell_list) {
        gen_list = inherit_genes(cell, nullptr);
        new_cells_list.push_back(new Cell(0, 0, Genome(gen_list)));
    }
    while (new_cells_list.size() < CELL_COUNT) {
        if (doRandomCell()) {
            gen_list = inherit_genes(env.cell_list[rand() % env.cell_list.size()], nullptr);
            new_cells_list.push_back(new Cell(0, 0, Genome(gen_list)));
        } else {
            new_cells_list.push_back(new Cell(0, 0, Genome()));
        }
    }
    env.clear();
    for (Cell *cell : new_cells_list)
        env.add_cell_to_rand_pos(cell);
}


void random_reproduce_cells(Environnement &env)
{
    vector<Cell *> new_cell_list;
    std::array<Gene, GENOME_LENGTH> gen_list{};
    int index_parent_1;
    int index_parent_2;
    Cell *cell;

    for (int i = 0; i < CELL_COUNT; i++){
        index_parent_1 = xorshift32() % env.cell_list.size();
#if (!ONE_PARENT == false)
            index_parent_2 = xorshift32() % env.cell_list.size();
            while (index_parent_2 == index_parent_1)
                index_parent_2 = xorshift32() % env.cell_list.size();
            gen_list = inherit_genes(env.cell_list[index_parent_1], env.cell_list[index_parent_2]);
#else
            gen_list = inherit_genes(env.cell_list[index_parent_1], nullptr);
#endif
        cell = new Cell(0, 0, Genome(gen_list));
        new_cell_list.push_back(cell);
    }
    env.clear();
    for (Cell *cell : new_cell_list)
        env.add_cell_to_rand_pos(cell);
}

void reproduce_cells(Environnement &env) {
#if RANDOM_REPRODUCE
    return random_reproduce_cells(env);
#else
    return linear_reproduce_cells(env);
#endif
}
