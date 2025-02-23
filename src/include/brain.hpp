#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>

class Brain {
    std::array<bool, INPUT_SIZE> inputUsed{};
    std::array<Neuron, LAYER_NEURON_LENGTH> layerNeurons{};
    std::array<Neuron, OUTPUT_SIZE> outputNeurons{};

    public:
        std::array<float, OUTPUT_SIZE> outputResults{};

        Brain();
        ~Brain();

        void activateNeuron(NEURON_TYPE neuron_type, int index);

        void addToNeurons(const Neuron_link &neuron_link);

        void setNeurons(const std::array<Neuron_link, GENOME_LENGTH>& neurone_link_list);

    void forward_cell(const std::vector<float> &input_list);
};

#endif
