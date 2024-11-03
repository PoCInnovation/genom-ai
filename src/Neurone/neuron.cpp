#include "neuron.hpp"
#include <stdlib.h>
#include <vector>

Neuron::Neuron()
{
}

Neuron::Neuron(INPUT_TYPE input_type)
{
    this->input_type = input_type;
}

Neuron::Neuron(OUTPUT_TYPE output_type, bool doTriggerOutput, float trigger_floor)
{
    this->output_type = output_type;
    this->doTriggerOutput = doTriggerOutput;
    this->trigger_floor = trigger_floor;
}

float Neuron::forward(std::vector<float> input_list)
{
    float res = 0.;

    if (this->neurone_type == INPUT_NEURON)
        res = input_list[this->input_size];
    else
        for (float input : input_list)
            res += input;
    res /= DEFAULT_INPUT_SIZE * input_list.size();
    if (this->doTriggerOutput)
        res = abs(res) > this->trigger_floor ? 1 : 0;
    return res;
}

Neuron::~Neuron()
{
}