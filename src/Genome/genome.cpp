#include <array>
#include <stdlib.h>
#include "genome.hpp"
#include "neuron_link.hpp"
#include "custom_random.hpp"
using namespace std;

Genome::Genome()
{
    for (int i = 0; i < GENOME_LENGTH; ++i)
        this->gen_list[i] = createRandomGene();
    
    for (int i = 0; i < GENOME_LENGTH; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::Genome(const std::array<Gene, GENOME_LENGTH> &gen_list)
{
    for (int i = 0; i < GENOME_LENGTH; ++i)
        this->gen_list[i] = gen_list[i];
    
    for (int i = 0; i < GENOME_LENGTH; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::~Genome()
= default;

Gene Genome::createRandomGene() {
    std::array<bool, GEN_LENGTH> bit_gen{};

#if GEN_LENGTH == 32
    unsigned int random_number = xorshift32();

    for (int i = 0; i < GEN_LENGTH; ++i)
        bit_gen[i] = (bool)(random_number & (1 << i));
#else
    for (int i = 0; i < GEN_LENGTH; ++i)
        bit_gen[i] = (xorshift32() % 2);
#endif

    return bit_gen;
}
