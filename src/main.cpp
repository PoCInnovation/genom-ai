#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
#include <iostream>
#include "loop.hpp"
#include "brain.hpp"
#include "render.hpp"
#include "genome.hpp"

using namespace std;

int main()
{
    sf::RenderWindow *window = nullptr;

    srand(time(0));
    loop(window);
    delete window;
    return 0;
}
