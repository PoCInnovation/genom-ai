#ifndef GENOME_HPP
#define GENOME_HPP

#include <cstdlib>
#include <array>
#include "simulation_parameters.hpp"
#include "neuron_link.hpp"

class Genome {
    public:
        std::array<Neuron_link, GENOME_LENGHT> neurone_link_list;
        std::array<std::array<bool, GEN_LENGHT>, GENOME_LENGHT> gen_list{};

        explicit Genome(std::array<long long, GENOME_LENGHT> genome);
        ~Genome();

        static std::array<bool, GEN_LENGHT> intToBitArray(long long gen);
};

#endif