#ifndef GENOME_HPP
#define GENOME_HPP

#include <cstdlib>
#include <array>
#include "simulation_parameters.hpp"
#include "neuron_link.hpp"

class Genome {
    private:
    public:
        std::array<Neuron_link, GENOME_LENGHT> neurone_link_list;
        std::array<std::array<bool, GEN_LENGHT>, GENOME_LENGHT> gen_list;

        Genome(std::array<long int, GENOME_LENGHT> genome);
        ~Genome();
        std::array<bool, GEN_LENGHT> intToBitArray(long int gen);
};

#endif