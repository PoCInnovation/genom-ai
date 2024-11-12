#include "neuron.hpp"
#include <vector>

Neuron::Neuron()
= default;

Neuron::Neuron(const INPUT_TYPE input)
{
    this->neurone_type = INPUT_NEURON;
    this->input_type = input;
}

Neuron::Neuron(const OUTPUT_TYPE output_type, const bool doTriggerOutput, const float trigger_floor)
{
    this->neurone_type = OUTPUT_NEURON;
    this->output_type = output_type;
    this->doTriggerOutput = doTriggerOutput;
    this->trigger_floor = trigger_floor;
}

float Neuron::calculate_neuron(std::vector<float> input_list)
{
    float res = 0.0f;

    if (this->neurone_type == INPUT_NEURON)
        return input_list[this->input_type];
    for (float input : input_list)
        res += input;
    if (input_list.size() == 0)
        res = 0;
    else
        res /= (float)DEFAULT_INPUT_SIZE * (float)input_list.size();
    if (this->doTriggerOutput)
        if (res > this->trigger_floor)
            res = 1.0f;
        else if (res < -this->trigger_floor)
            res = -1.0f;
        else
            res = 0.0f;
    return res;
}

Neuron::~Neuron()
= default;
