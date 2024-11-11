#ifndef GENOME_HPP
#define GENOME_HPP

#include <cstdlib>
#include <array>
#include "simulation_parameters.hpp"
#include "neuron_link.hpp"

typedef std::array<bool, GEN_LENGHT> Gene;

class Genome {
    public:
        std::array<Neuron_link, GENOME_LENGHT> neurone_link_list;
        std::array<Gene, GENOME_LENGHT> gen_list{};

        Genome();
        explicit Genome(std::array<long long, GENOME_LENGHT> genome);
        void setGenList(std::array<Gene, GENOME_LENGHT> gen_list);
        static Gene intToBitArray(long long gen);
        ~Genome();
};

#endif
