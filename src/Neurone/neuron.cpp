#include "neuron.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

Neuron::Neuron()
= default;

void Neuron::add_input(const Neuron_link& input) {
    this->inputs.push_back(input);
}

void Neuron::calculate_neuron(const std::vector<float> &input_list,
                              const std::array<Neuron, LAYER_NEURON_LENGTH> &layer) {
    float res = 0.0f;

    for (const Neuron_link& link : this->inputs) {
        if (link.in_neuron == INPUT_NEURON)
            res += link.weight * input_list[link.in_index];
        else
            res += link.weight * layer[link.in_index].value;
    }
    this->value = std::tanh(res);
}

Neuron::~Neuron()
= default;
