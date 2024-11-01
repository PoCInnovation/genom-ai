#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "simulation_parameters.hpp"
#include "cell.hpp"

using namespace std;

void draw_cells(vector<vector<Cell *>> &cell_list, sf::RenderWindow *window)
{
    sf::CircleShape shape(min(WINDOW_SIZE_X, WINDOW_SIZE_Y) / CELL_COUNT / 2);

    shape.setFillColor(sf::Color::Green);
    for (int y = 0; y < GRID_SIZE_Y; y++) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            if (cell_list[y][x] != nullptr){
                shape.setPosition((x * WINDOW_SIZE_X) / GRID_SIZE_X, (y * WINDOW_SIZE_Y) / GRID_SIZE_Y);
                window->draw(shape);
            }
        }
    }
}

void render(vector<vector<Cell *>> &cell_list, sf::RenderWindow *window)
{
    sf::Event event;

    if (RENDER == false)
        return;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window->close();
    if (!window->isOpen())
        exit(0);
    draw_cells(cell_list, window);
    window->display();
    sf::sleep(sf::seconds(1./FPS));
    window->clear();
}
