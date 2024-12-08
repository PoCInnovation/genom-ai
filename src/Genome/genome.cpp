#include "genome.hpp"
#include "neuron_link.hpp"
#include <array>
#include <cstdlib>
using namespace std;

Genome::Genome()
{
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = createRandomGene();
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::Genome(const std::array<Gene, GENOME_LENGHT> &gen_list)
{
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->gen_list[i] = gen_list[i];
    
    for (int i = 0; i < GENOME_LENGHT; ++i)
        this->neurone_link_list[i] = Neuron_link(gen_list[i]);
}

Genome::~Genome()
= default;

Gene Genome::createRandomGene() {
    std::array<bool, GEN_LENGHT> bit_gen{};

    for (int i = 0; i < GEN_LENGHT; ++i)
        bit_gen[i] = (rand() % 2);
    return bit_gen;
}

sf::Color Genome::getColor() const {
    int input = 0;
    int layer = 0;
    int output = 0;
    for (const Neuron_link& link : this->neurone_link_list) {
        if (link.in_neuron == INPUT_NEURON)
            ++input;
        else
            ++layer;
        if (link.out_neuron == OUTPUT_NEURON)
            ++output;
        else
            ++layer;
    }
    return sf::Color(input * (255 / GENOME_LENGHT), layer * (127 / GENOME_LENGHT), output * (255 / GENOME_LENGHT));
}


