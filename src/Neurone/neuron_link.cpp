#include <array>
#include "neuron_link.hpp"

Neuron_link::Neuron_link(std::array<bool, GEN_LENGHT> gen)
{
    this->in_neuron = gen[0] ? INPUT_NEURON : LAYER_NEURON;
    for (int i = 1; i < INDEX_SIZE; ++i)
        this->in_index = (this->in_index << 1) + gen[i];
    this->out_neuron = gen[INDEX_SIZE] ? LAYER_NEURON : OUTPUT_NEURON;
    for (int i = INDEX_SIZE; i < 2 * INDEX_SIZE; ++i)
        this->out_index= (this->out_index << 1) + gen[i];
    for (int i = 2 * INDEX_SIZE; i < GEN_LENGHT; ++i)
        this->weight = (this->weight << 1) + gen[i];
}

Neuron_link::Neuron_link()
{
}

Neuron_link::~Neuron_link()
{
}
