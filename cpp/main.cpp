#include <SFML/Graphics.hpp>
#include "simulation_parameters.hpp"
#include "loop.hpp"

using namespace std;

int main()
{
    sf::RenderWindow *window = nullptr;

    if (RENDER)
        window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
    srand(time(0));
    loop(window);
    return 0;
}
