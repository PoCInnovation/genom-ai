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

static Gene get_gene(int link_index, Cell *parent1, Cell *parent2)
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

static std::array<Gene, GENOME_LENGTH> inherit_genes(Cell *parent1, Cell *parent2)
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

void reproduce_cells(Environnement &env)
{
    vector<Cell *> new_cell_list;
    std::array<Gene, GENOME_LENGTH> gen_list{};
    int index_parent_1;
    int index_parent_2;
    Cell *cell;

    for (int i = 0; i < CELL_COUNT; i++){
        index_parent_1 = xorshift32() % env.cell_list.size();
#if ONE_PARENT == true
        gen_list = inherit_genes(env.cell_list[index_parent_1], nullptr);
#else
        index_parent_2 = xorshift32() % env.cell_list.size();
        while (index_parent_2 == index_parent_1)
            index_parent_2 = xorshift32() % env.cell_list.size();
        gen_list = inherit_genes(env.cell_list[index_parent_1], env.cell_list[index_parent_2]);
#endif
        cell = new Cell(0, 0, Genome(gen_list));
        new_cell_list.push_back(cell);
    }
    env.clear();
    for (Cell *cell : new_cell_list)
        env.add_cell_to_rand_pos(cell);
}
