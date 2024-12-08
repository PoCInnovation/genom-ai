#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

#include "neuron_link.hpp"

class Neuron {

public:
    bool isActive = false;
    std::vector<Neuron_link> inputs;
    float value = 0.0f;

    Neuron();

    void add_input(const Neuron_link& input);

    void calculate_neuron(const std::vector<float> &input_list, const std::array<Neuron, LAYER_NEURON_LENGHT> &layer);

    ~Neuron();
};

#endif
