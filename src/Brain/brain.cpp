#include "brain.hpp"

#include <iostream>
#include <vector>

using namespace std;

Brain::Brain()
= default;

Brain::~Brain()
= default;

array<float, OUTPUT_SIZE> Brain::forward(const vector<float>& input_list, array<Neuron_link, GENOME_LENGHT>& neuron_links)
{
    array<float, OUTPUT_SIZE> output{};
    this->input.fill(EMPTY_VALUE);
    this->layer.fill(EMPTY_VALUE);

    for (int i = 0; i < OUTPUT_SIZE; i++)
        output[i] = this->calculate_output(input_list, neuron_links, i, OUTPUT_NEURON);
    return output;
}

float Brain::calculate_output(const std::vector<float>& input_list, std::array<Neuron_link, GENOME_LENGHT>& neuron_links, int index, NEURON_TYPE neuron_type)
{
    float result = 0.0f;
    vector<float> output;

    // INPUT NEURON
    if (neuron_type == INPUT_NEURON) {
        if (this->input[index] != EMPTY_VALUE)
            return this->input[index];
        result = this->input_neurons[index].calculate_neuron(input_list);
        this->input[index] = result;
        return result;
    }

    // ALREADY CALCULATED LAYER NEURON
    if (neuron_type == LAYER_NEURON && this->layer[index] != EMPTY_VALUE)
        return this->layer[index];

    // CALCULATE NEURON
    for (int i = 0; i < GENOME_LENGHT; i++) {
        Neuron_link& link = neuron_links[i];
        if (link.in_neuron == link.out_neuron)
            continue;
        if (!link.active_neuron || link.out_neuron != neuron_type || link.out_index != index)
            continue;
        output.push_back(this->calculate_output(input_list, neuron_links, link.in_index, link.in_neuron) * link.weight);
    }

    // SAVE LAYER NEURON
    if (neuron_type == LAYER_NEURON) {
        result = 0.0f;
        for (const float out : output)
            result += out;
        result /= (float)output.size() * (float)DEFAULT_OUTPUT_SIZE;
        this->layer[index] = result;
        return result;
    }
    return this->output_neurons[index].calculate_neuron(output);
}
