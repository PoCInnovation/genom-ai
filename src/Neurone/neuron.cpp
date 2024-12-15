#include "neuron.hpp"

#include <array>
#include <cmath>
#include <iostream>
#include <vector>

Neuron::Neuron()
= default;

Neuron::Neuron(const NEURON_TYPE neuron_type, const int index) {
    this->neuron_type = neuron_type;
    this->index = index;
}

void Neuron::add_input(const Neuron_link& input) {
    this->inputs.push_back(input);
}

float Neuron::calculate_neuron(const std::vector<float> &input_list, const std::array<float, LAYER_NEURON_LENGTH>& layer) const {
    float res = 0.0f;

    for (const Neuron_link& link : this->inputs) {
        if (link.in_neuron == INPUT_NEURON)
            res += link.weight * input_list[link.in_index];
        else
            res += link.weight * layer[link.in_index];
    }
    res = std::tanh(res);
    if (this->neuron_type == OUTPUT_NEURON) {
        if (res > 0.5f)
            res = 1.0f;
        else if (res < -0.5f)
            res = -1.0f;
        else
            res = 0.0f;
    }
    return res;
}

Neuron::~Neuron()
= default;
