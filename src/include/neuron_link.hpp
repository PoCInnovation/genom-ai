#ifndef NEURON_LINK_HPP
#define NEURON_LINK_HPP

#include "simulation_parameters.hpp"

typedef std::array<bool, GEN_LENGTH> Gene;

#define INDEX_SIZE 8

#define DEFAULT_INPUT_SIZE 1
#define DEFAULT_OUTPUT_SIZE 1

enum INPUT_TYPE {
    X_POS,
    Y_POS,
    CONST_1,
    CONST_0,
    CONST_MINUS_1,
    CONST_HALF,
    CONST_MINUS_HALF,
    INPUT_SIZE
};

enum OUTPUT_TYPE {
    X_MOV,
    Y_MOV,
    OUTPUT_SIZE
};

enum NEURON_TYPE {
    INPUT_NEURON,
    LAYER_NEURON,
    OUTPUT_NEURON
};

class Neuron_link {
    public:
        NEURON_TYPE in_neuron = INPUT_NEURON;
        int in_index = -1;
        NEURON_TYPE out_neuron = OUTPUT_NEURON;
        int out_index = -1;
        float weight = -1;
        bool active_neuron = true;

        Neuron_link();
        explicit Neuron_link(const Gene &gen);

        void print() const;

        void PrintInfo() const;
        ~Neuron_link();
};

#endif
