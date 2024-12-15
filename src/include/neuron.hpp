#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

#include "neuron_link.hpp"

class Neuron {

public:
    std::vector<Neuron_link> inputs;
    NEURON_TYPE neuron_type = LAYER_NEURON;
    int index = 0;

    Neuron();

    explicit Neuron(NEURON_TYPE neuron_type, int index);

    void add_input(const Neuron_link& input);

    float calculate_neuron(const std::vector<float> &input_list, const std::array<float, LAYER_NEURON_LENGTH>& layer) const;

    ~Neuron();
};

#endif
