#ifndef GENOME_HPP
#define GENOME_HPP

#include <array>
#include "simulation_parameters.hpp"
#include "neuron_link.hpp"
#include "SFML/Graphics/Color.hpp"

class Genome {
    public:
        std::array<Neuron_link, GENOME_LENGTH> neurone_link_list;
        std::array<Gene, GENOME_LENGTH> gen_list{};

        Genome();
        explicit Genome(const std::array<Gene, GENOME_LENGTH> &gen_list);
        static Gene createRandomGene();
        std::array<Neuron_link, GENOME_LENGTH> getLinkList() const {return neurone_link_list;}
        std::array<Gene, GENOME_LENGTH> getGenomeList() const {return gen_list;}
        sf::Color getColor() const;

        ~Genome();
};

#endif
