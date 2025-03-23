#ifndef BRAIN_HPP
#define BRAIN_HPP

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>

#include "Interfaces/ibrain.hpp"

class Brain : public virtual IBrain {
    std::array<bool, INPUT_SIZE> inputUsed{};
    std::array<float, LAYER_NEURON_LENGTH> layer_values{};
    std::array<INeuron *, LAYER_NEURON_LENGTH> layerNeurons{};
    std::array<INeuron *, OUTPUT_SIZE> outputNeurons{};

    public:
        std::array<float, OUTPUT_SIZE> outputResults{};

        Brain();
        ~Brain() override;
        void activateNeuron(NEURON_TYPE neuron_type, int index) override;
        void addToNeurons(const Neuron_link &neuron_link) override;
        void setNeurons(const std::array<Neuron_link, GENOME_LENGTH>& neurone_link_list) override;
        void forward_cell(const std::vector<float> &input_list) override;
        std::array<float, OUTPUT_SIZE> getOutputs() const override {return outputResults;}
};

#endif
