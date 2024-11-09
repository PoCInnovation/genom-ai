#include "brain.hpp"
#include <vector>

Brain::Brain()
{
}

Brain::~Brain()
{
}

std::array<float, OUTPUT_SIZE> Brain::forward(std::vector<float> input_list, std::array<Neuron_link, GENOME_LENGHT> neuron_links)
{
    std::vector<float> input_results = this->forward_inputs(input_list, neuron_links);
    std::array<std::vector<float>, OUTPUT_SIZE>
}

std::vector<float> Brain::forward_inputs(std::vector<float> input_list, std::array<Neuron_link, GENOME_LENGHT> neuron_links)
{
    std::vector<float> res(INPUT_SIZE, 0.0);

    for (int i = 0; i < GENOME_LENGHT; ++i)
        if (neuron_links[i].active_neuron && neuron_links[i].in_neuron == INPUT_NEURON)
            res[i] = this->input_neurons[neuron_links[i].in_index % INPUT_SIZE].forward(input_list);
    return res;
}