#include "cell.hpp"

#include "custom_random.hpp"
#include "genome.hpp"


Cell::Cell(const int x, const int y, const Genome& genome)
    : brain()
{
    Cell::setPos(x, y);
    this->genome = genome;
    this->brain = new Brain();
    this->brain->setNeurons(genome.getLinkList());
    this->color = this->genome.getColor();
}

void Cell::setPos(const int x, const int y)
{
    this->x = x;
    this->y = y;
}

Cell::~Cell()
= default;

static bool mutation_happen()
{
    return (xorshift32() % 10000) <= MUTATION_CHANCE;
}

static void mutate(Gene &gen)
{
    const int index = xorshift32() % GEN_LENGTH;

    gen[index] = !gen[index];
}


ICell *Cell::reproduce() {
    std::array<Gene, GENOME_LENGTH> gen_list = genome.getGenomeList();

    for (auto &gene : gen_list)
        if (mutation_happen())
            mutate(gene);
    return new Cell(0, 0, Genome(gen_list));
}

ICell *Cell::reproduce(ICell *other) {
    const Cell *other_cell = dynamic_cast<Cell *>(other);
    if (!other_cell)
        return reproduce();
    std::array<Gene, GENOME_LENGTH> gen_list = genome.getGenomeList();
    const std::array<Gene, GENOME_LENGTH> other_gen_list = other_cell->genome.getGenomeList();
    for (int i = 0; i < GENOME_LENGTH; i++) {
        if (xorshift32() % 2 == 0)
            gen_list[i] = other_gen_list[i];
        if (mutation_happen())
            mutate(gen_list[i]);
    }
    return new Cell(0, 0, Genome(gen_list));
}

std::array<float, OUTPUT_SIZE> Cell::getOutputs() const {
    return this->brain->getOutputs();
}

void Cell::forwardCell(const std::vector<float> inputList) {
    this->brain->forward_cell(inputList);
}
