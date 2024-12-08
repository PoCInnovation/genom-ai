#include "brain.hpp"

#include <iostream>
#include <vector>
#include <array>

#include "cell.hpp"

using namespace std;

Brain::Brain()
= default;

Brain::~Brain()
= default;

void Brain::setNeurons(const std::array<Neuron_link, GENOME_LENGHT>& neurone_link_list) {
    for (const Neuron_link& neuron_link : neurone_link_list) {
        addToNeurons(neuron_link);
    }
}

void Brain::addToNeurons(const Neuron_link& neuron_link) {
    if (neuron_link.out_neuron == LAYER_NEURON)
        this->layerNeurons[neuron_link.out_index].add_input(neuron_link);
    else
        this->outputNeurons[neuron_link.out_index].add_input(neuron_link);
}

static float roundOutputResult(const float res) {
    if (res > 0.5f)
        return 1.0f;
    if (res < -0.5f)
        return -1.0f;
    return 0.0f;
}

array<float, OUTPUT_SIZE> Brain::forward_cell(const vector<float> &input_list) {

    array<float, OUTPUT_SIZE> output{};

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        Neuron& neuron = this->outputNeurons[i];
        neuron.calculate_neuron(input_list, this->layerNeurons);
        output[i] = roundOutputResult(neuron.value);
    }
    for (Neuron& neuron : this->layerNeurons) {
        neuron.calculate_neuron(input_list, this->layerNeurons);
    }
    return output;
}
