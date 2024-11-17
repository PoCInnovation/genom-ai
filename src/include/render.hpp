#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "environnement.hpp"

#define WINDOW_SIZE_X 1300
#define WINDOW_SIZE_Y 800

void render(Environnement &env, sf::RenderWindow *window, int gen_number);

#endif
