#ifndef LOOP_HPP
#define LOOP_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "environnement.hpp"

int compute_step(Environnement &env);
int loop(sf::RenderWindow *window);

#endif
