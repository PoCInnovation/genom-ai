#include "genome.hpp"
#include "neuron_link.hpp"
#include <array>
#include <iostream>
using namespace std;

Genome::Genome(std::array<long long, GENOME_LENGHT> genome)
{
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = intToBitArray(genome[i]);
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::~Genome()
= default;

std::array<bool, GEN_LENGHT> Genome::intToBitArray(const long long gen)
{
    std::array<bool, GEN_LENGHT> bit_gen{};

    for (int i = 0; i < GEN_LENGHT; ++i)
        bit_gen[i] = (gen >> i) % 2;
    return bit_gen;
}