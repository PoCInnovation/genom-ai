#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>

class Brain {
    private:
        std::vector<float> forward_inputs(std::vector<float> input_list, std::array<Neuron_link, GENOME_LENGHT> neuron_links);

    public:
        std::array<Neuron, INPUT_SIZE> input_neurons = {
            Neuron(X_POS),
            Neuron(Y_POS)
        };
        std::array<Neuron, OUTPUT_SIZE> output_neurons = {
            Neuron(X_MOV, true, 0.5),
            Neuron(Y_MOV, true, 0.5),
        };
        Neuron layer_neuron = Neuron();

        Brain();
        ~Brain();
        std::array<float, OUTPUT_SIZE> forward(std::vector<float> input_list, std::array<Neuron_link, GENOME_LENGHT> neuron_links);
};

#endif
