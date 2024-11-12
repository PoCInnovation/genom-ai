#include "genome.hpp"
#include "neuron_link.hpp"
#include <array>
#include <iostream>
using namespace std;

Genome::Genome()
{
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = intToBitArray(rand());
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::Genome(std::array<long long, GENOME_LENGHT> genome)
{  
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = intToBitArray(genome[i]);
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

void Genome::setGenList(std::array<Gene, GENOME_LENGHT> gen_list)
{
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = gen_list[i];
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::~Genome()
= default;

Gene Genome::intToBitArray(const long long gen) {
    std::array<bool, GEN_LENGHT> bit_gen{};

    for (int i = 0; i < GEN_LENGHT; ++i)
        bit_gen[i] = (gen >> i) % 2;
    return bit_gen;
}
