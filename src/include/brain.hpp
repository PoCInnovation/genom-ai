#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>

#define EMPTY_VALUE (-2.0f)

class Brain {
    private:

        std::array<float, INPUT_SIZE> input{};
        std::array<float, LAYER_NEURON_LENGHT> layer{};

        float calculate_output(const std::vector<float>& input_list, std::array<Neuron_link, GENOME_LENGHT>& neuron_links, int index, NEURON_TYPE neuron_type);

    public:
        std::array<Neuron, INPUT_SIZE> input_neurons = {
            Neuron(X_POS),
            Neuron(Y_POS),
            Neuron(CONST_1),
            Neuron(CONST_0),
            Neuron(CONST_MINUS_1),
            Neuron(CONST_HALF),
            Neuron(CONST_MINUS_HALF)
        };
        std::array<Neuron, OUTPUT_SIZE> output_neurons = {
            Neuron(X_MOV, true, 0.2f),
            Neuron(Y_MOV, true, 0.2f),
        };
        Neuron layer_neuron = Neuron();

        Brain();
        ~Brain();
        std::array<float, OUTPUT_SIZE> forward(const std::vector<float>& input_list, std::array<Neuron_link, GENOME_LENGHT>& neuron_links);
};

#endif
