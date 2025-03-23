#include "brain.hpp"

#include <iostream>
#include <vector>
#include <array>

#include "cell.hpp"

using namespace std;

Brain::Brain() {
    for (size_t i = 0; i < LAYER_NEURON_LENGTH; ++i)
        layerNeurons[i] = new Neuron();
    for (size_t i = 0; i < OUTPUT_SIZE; ++i)
        outputNeurons[i] = new Neuron();
};

Brain::~Brain() = default;

void Brain::activateNeuron(const NEURON_TYPE neuron_type, int index) {
    if (neuron_type == INPUT_NEURON) {
        this->inputUsed[index] = true;
        return;
    }
    INeuron *neuron = this->layerNeurons[index];
    if (neuron->isActive())
        return;
    neuron->setActive(true);
    for (const Neuron_link& neuron_link : neuron->getInputs()) {
        activateNeuron(neuron_link.in_neuron, neuron_link.in_index);
    }
}

void Brain::setNeurons(const std::array<Neuron_link, GENOME_LENGTH>& neurone_link_list) {
    for (const Neuron_link& neuron_link : neurone_link_list) {
        addToNeurons(neuron_link);
    }

    for (const INeuron *neuron : this->outputNeurons) {
        for (const Neuron_link& neuron_link : neuron->getInputs()) {
            activateNeuron(neuron_link.in_neuron, neuron_link.in_index);
        }
    }
}

void Brain::addToNeurons(const Neuron_link& neuron_link) {
    if (neuron_link.out_neuron == LAYER_NEURON)
        this->layerNeurons[neuron_link.out_index]->add_input(neuron_link);
    else
        this->outputNeurons[neuron_link.out_index]->add_input(neuron_link);
}

static float roundOutputResult(const float res) {
    if (res > 0.5f)
        return 1.0f;
    if (res < -0.5f)
        return -1.0f;
    return 0.0f;
}

void Brain::forward_cell(const vector<float> &input_list) {

    std::array<float, LAYER_NEURON_LENGTH> layer_results{};
    for (size_t i = 0; i < LAYER_NEURON_LENGTH; i++) {
        if (this->layerNeurons[i]->isActive())
            layer_results[i] = this->layerNeurons[i]->calculate_neuron(input_list, this->layer_values);
    }
    for (int i = 0; i < OUTPUT_SIZE; i++) {
        this->outputResults[i] = roundOutputResult(this->layerNeurons[i]->calculate_neuron(input_list, this->layer_values));
    }
    this->layer_values = layer_results;
}
