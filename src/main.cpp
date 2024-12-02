#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <array>
#include <iostream>
#include <sys/time.h>
#include "loop.hpp"
#include "brain.hpp"
#include "render.hpp"
#include "genome.hpp"
#include "custom_random.hpp"

using namespace std;

extern unsigned int xor_seed;

#if REPLAY_MODE == false
int main()
{
    sf::RenderWindow *window = nullptr;

    srand(time(nullptr));
    xor_seed = rand();
    loop(window);
    delete window;
    return 0;
}
#endif
