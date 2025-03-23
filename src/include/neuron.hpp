#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

#include "neuron_link.hpp"
#include "Interfaces/ineuron.hpp"

class Neuron : public virtual INeuron {

    bool active = false;
    std::vector<Neuron_link> inputs;

public:
    Neuron();
    void add_input(const Neuron_link& input) override;
    float calculate_neuron(const std::vector<float> &input_list, const std::array<float, LAYER_NEURON_LENGTH> &layer) override;
    bool isActive() const override {return active;};
    void setActive(const bool active) override {this->active = active;}
    std::vector<Neuron_link> getInputs() const override {return inputs;}
    ~Neuron() override;
};

#endif
