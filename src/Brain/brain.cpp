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
    for (Neuron& neuron : this->neurons)
        if (neuron.neuron_type == neuron_link.out_neuron && neuron.index == neuron_link.out_index) {
            neuron.add_input(neuron_link);
            return;
        }
    Neuron new_neuron(neuron_link.out_neuron, neuron_link.out_index);
    new_neuron.add_input(neuron_link);
    this->neurons.push_back(new_neuron);
}

array<float, OUTPUT_SIZE> Brain::forward_cell(const vector<float> &input_list) {

    array<float, OUTPUT_SIZE> output{};
    float result = 0;

    for (Neuron& neuron : this->neurons) {
        result = neuron.calculate_neuron(input_list, this->layer);
        if (neuron.neuron_type == LAYER_NEURON)
            this->layer[neuron.index] = result;
        else
            output[neuron.index] = result;
    }
    return output;
}
