#ifndef INEURON_H
#define INEURON_H
#include "neuron.hpp"

class INeuron {
public:
    virtual ~INeuron() = default;
    virtual void add_input(const Neuron_link& input) = 0;
    virtual float calculate_neuron(const std::vector<float> &input_list, const std::array<float, LAYER_NEURON_LENGTH> &layer) = 0;
    virtual bool isActive() const = 0;
    virtual void setActive(bool active) = 0;
    virtual std::vector<Neuron_link> getInputs() const = 0;
};

#endif //INEURON_H
