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

float Neuron::calculate_neuron(std::vector<float> input_list) const
{
    float res = 0.;

    if (this->neurone_type == INPUT_NEURON)
        return input_list[this->input_type];
    for (const float input : input_list)
        res += input;
    res /= DEFAULT_INPUT_SIZE * input_list.size();
    if (this->doTriggerOutput)
        if (res > this->trigger_floor)
            res = 1;
        else if (res < -this->trigger_floor)
            res = -1;
        else
            res = 0;
    return res;
}

Neuron::~Neuron()
= default;
