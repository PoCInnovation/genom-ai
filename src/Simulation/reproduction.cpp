#include <random>
#include <vector>
#include "simulation_parameters.hpp"
#include "cell.hpp"
#include "environnement.hpp"
#include "genome.hpp"

using namespace std;

static bool mutation_happen()
{
    return (rand() % 10000) <= MUTATION_CHANCE;
}

static Gene get_gene(int link_index, Cell *parent1, Cell *parent2)
{
    int rand_number = rand();

    if (rand_number % 2 == 0)
        return parent1->genome.gen_list[link_index];
    else
        return parent2->genome.gen_list[link_index];
}

static void mutate(Gene &gen)
{
    int index = rand() % GEN_LENGHT;

    gen[index] = !gen[index];
}

static void inherit_genes(Cell *child_cell, Cell *parent1, Cell *parent2)
{
    std::array<Gene, GENOME_LENGHT> gen_list;

    for (int i = 0; i < GENOME_LENGHT; i++){
        gen_list[i] = get_gene(i, parent1, parent2);
        if (mutation_happen())
            mutate(gen_list[i]);
    }
    child_cell->genome.setGenList(gen_list);
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

void reproduce_cells(Environnement &env)
{
    vector<Cell *> new_cell_list;
    int index_parent_1;
    int index_parent_2;
    Cell *cell;

    for (int i = 0; i < CELL_COUNT; i++){
        cell = new Cell(0, 0, Genome());
        index_parent_1 = rand() % env.cell_list.size();
        index_parent_2 = rand() % env.cell_list.size();
        while (index_parent_2 == index_parent_1)
            index_parent_2 = rand() % env.cell_list.size();
        inherit_genes(cell, env.cell_list[index_parent_1], env.cell_list[index_parent_2]);
        new_cell_list.push_back(cell);
    }
    env.clear();
    for (Cell *cell : new_cell_list)
        env.add_cell_to_rand_pos(cell);
}
