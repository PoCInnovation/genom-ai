#include <array>
#include "neuron_link.hpp"

#include <complex>

Neuron_link::Neuron_link(std::array<bool, GEN_LENGHT> gen)
{
    int res = 0;
    this->in_neuron = gen[0] ? INPUT_NEURON : LAYER_NEURON;
    for (int i = 1; i < INDEX_SIZE; ++i)
        res = (res << 1) + gen[i];
    this->in_index = res % INPUT_SIZE;
    this->out_neuron = gen[INDEX_SIZE] ? LAYER_NEURON : OUTPUT_NEURON;
    for (int i = INDEX_SIZE; i < 2 * INDEX_SIZE; ++i)
        res = (res << 1) + gen[i];
    this->out_index = res % OUTPUT_SIZE;
    for (int i = 2 * INDEX_SIZE; i < GEN_LENGHT; ++i)
        res = (res << 1) + gen[i];
    this->weight = (res / pow(2, GEN_LENGHT - 4)) - DEFAULT_INPUT_SIZE;
}

Neuron_link::Neuron_link()
= default;

Neuron_link::~Neuron_link()
= default;
