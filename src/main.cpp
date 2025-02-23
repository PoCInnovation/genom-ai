#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>
#include <sys/time.h>
#include "loop.hpp"
#include "render.hpp"
#include "genome.hpp"

using namespace std;

extern unsigned int xor_seed;

#if !REPLAY_MODE
int main()
{
    sf::RenderWindow *window = nullptr;

    srand(time(nullptr));
    xor_seed = static_cast<unsigned int>(time(nullptr));
    loop(window);
    delete window;
    return 0;
}
#endif
