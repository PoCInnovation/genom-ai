#ifndef NEURON_LINK_HPP
#define NEURON_LINK_HPP

#include <array>
#include "neuron.hpp"
#include "simulation_parameters.hpp"

#define INDEX_SIZE 8

class Neuron_link {
    private:
        /* data */
    public:
        NEURON_TYPE in_neuron = INPUT_NEURON;
        int in_index = 0;
        NEURON_TYPE out_neuron = OUTPUT_NEURON;
        int out_index = 0;
        int weight = 0;
        bool active_neuron = true;

        Neuron_link();
        Neuron_link(std::array<bool, GEN_LENGHT> gen);
        ~Neuron_link();
};

#endif
