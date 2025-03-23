
#ifndef IBRAIN_H
#define IBRAIN_H

#include "neuron.hpp"
#include "neuron_link.hpp"
#include <array>


class IBrain {
public:
    virtual ~IBrain() = default;
    virtual void activateNeuron(NEURON_TYPE neuron_type, int index) = 0;
    virtual void addToNeurons(const Neuron_link &neuron_link) = 0;
    virtual void setNeurons(const std::array<Neuron_link, GENOME_LENGTH>& neurone_link_list) = 0;
    virtual void forward_cell(const std::vector<float> &input_list) = 0;
    virtual std::array<float, OUTPUT_SIZE> getOutputs() const = 0;
};

#endif //IBRAIN_H
