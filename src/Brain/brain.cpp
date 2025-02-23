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

void Brain::activateNeuron(const NEURON_TYPE neuron_type, int index) {
    if (neuron_type == INPUT_NEURON) {
        this->inputUsed[index] = true;
        return;
    }
    Neuron &neuron = this->layerNeurons[index];
    if (neuron.isActive)
        return;
    neuron.isActive = true;
    for (const Neuron_link& neuron_link : neuron.inputs) {
        activateNeuron(neuron_link.in_neuron, neuron_link.in_index);
    }
}

void Brain::setNeurons(const std::array<Neuron_link, GENOME_LENGTH>& neurone_link_list) {
    for (const Neuron_link& neuron_link : neurone_link_list) {
        addToNeurons(neuron_link);
    }

    for (const Neuron& neuron : this->outputNeurons) {
        for (const Neuron_link& neuron_link : neuron.inputs) {
            activateNeuron(neuron_link.in_neuron, neuron_link.in_index);
        }
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

void Brain::forward_cell(const vector<float> &input_list) {

    for (int i = 0; i < OUTPUT_SIZE; i++) {
        Neuron& neuron = this->outputNeurons[i];
        neuron.calculate_neuron(input_list, this->layerNeurons);
        this->outputResults[i] = roundOutputResult(neuron.value);
    }
    for (Neuron& neuron : this->layerNeurons) {
        if (neuron.isActive)
            neuron.calculate_neuron(input_list, this->layerNeurons);
    }
}
