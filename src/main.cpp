#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
#include <iostream>

#include "brain.hpp"
#include "render.hpp"
#include "genome.hpp"

using namespace std;

int main()
{
    sf::RenderWindow *window = nullptr;
    constexpr array<long long, 16> gen_list = {2630649863,2234318291,587519384,4046790627,198891543,2930195345,2430034330,1259062384,165362935,2032222446,2000319283,3672401751,1150821254,804153190,249780784,3014943375};
    const vector<float> inputs = {1, 1};
    const Genome genome(gen_list);
    Brain brain{};
  
    srand(time(0));
    brain.forward(inputs, genome.neurone_link_list);
    loop(window);
    delete window;
    return 0;
}
