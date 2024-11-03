#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>

enum NEURON_TYPE {
    INPUT_NEURON,
    LAYER_NEURON,
    OUTPUT_NEURON
};

enum INPUT_TYPE {
    X_SIZE,
    Y_SIZE,
    X_POS,
    Y_POS,
    INPUT_SIZE
};

enum OUTPUT_TYPE {
    X_MOV,
    Y_MOV,
    OUTPUT_SIZE
};

#define DEFAULT_INPUT_SIZE 4
#define DEFAULT_OUTPUT_SIZE 4

class Neuron {
    private:

        float input_size = DEFAULT_INPUT_SIZE;
        float output_size = DEFAULT_OUTPUT_SIZE;

    public:

        NEURON_TYPE neurone_type = LAYER_NEURON;
        INPUT_TYPE input_type;
        OUTPUT_TYPE output_type;

        bool doTriggerOutput = false;
        float trigger_floor;

        Neuron();
        Neuron(INPUT_TYPE input);
        Neuron(OUTPUT_TYPE output_type, bool doTriggerOutput, float trigger_floor);
        float forward(std::vector<float> input_list);
        ~Neuron();
};

#endif