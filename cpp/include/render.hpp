#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include "cell.hpp"

void draw_cells(std::vector<std::vector<Cell *>> &cell_list, sf::RenderWindow *window);
void render(std::vector<std::vector<Cell *>> &cell_list, sf::RenderWindow *window);

#endif
