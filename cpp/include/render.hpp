#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "cell.hpp"
#include "environnement.hpp"

#define WINDOW_SIZE_X 800
#define WINDOW_SIZE_Y 800

void render(Environnement &env, sf::RenderWindow *window);

#endif
