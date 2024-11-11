#include <array>
#include <complex>
#include "neuron_link.hpp"
#include "genome.hpp"
#include <iostream>

Neuron_link::Neuron_link(Gene gen)
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

void Neuron_link::PrintInfo(void)
{
    printf("Neuron\n");
    printf("active: %d\n", (int)this->active_neuron);
    printf("in neuron index: %d\n", this->in_index);
    printf("out neuron index: %d\n", this->out_index);
    printf("weight: %f\n", this->weight);
}

Neuron_link::Neuron_link()
= default;

Neuron_link::~Neuron_link()
= default;
