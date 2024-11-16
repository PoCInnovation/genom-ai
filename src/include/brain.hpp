#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>

#define EMPTY_VALUE (-2.0f)

class Brain {
    std::array<float, LAYER_NEURON_LENGHT> layer{};

    public:

        std::vector<Neuron> neurons;
        Brain();
        ~Brain();

        void addToNeurons(const Neuron_link &neuron_link);

        void setNeurons(const std::array<Neuron_link, GENOME_LENGHT>& neurone_link_list);

        std::array<float, OUTPUT_SIZE> forward_cell(const std::vector<float> &input_list);
};

#endif
