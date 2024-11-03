#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "loop.hpp"
#include "genome.hpp"

using namespace std;

int main()
{
    std::array<long int, 16> gen_list = {2630649863,2234318291,587519384,4046790627,198891543,2930195345,2430034330,1259062384,165362935,2032222446,2000319283,3672401751,1150821254,804153190,249780784,3014943375};
    Genome genome(gen_list);
    return 0;
}
