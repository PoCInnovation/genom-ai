#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "simulation_parameters.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"

using namespace std;

static void draw_cells(Environnement &env, sf::RenderWindow *window)
{
    sf::CircleShape shape(min(WINDOW_SIZE_X, WINDOW_SIZE_Y) / CELL_COUNT / 2);

    shape.setFillColor(sf::Color::Green);
    for (Cell *cell : env.cell_list){
        shape.setPosition((cell->x * WINDOW_SIZE_X) / GRID_SIZE_X, (cell->y * WINDOW_SIZE_Y) / GRID_SIZE_Y);
        window->draw(shape);
    }
}

void render(Environnement &env, sf::RenderWindow *window)
{
    sf::Event event;

    if (RENDER == false)
        return;
    while (window->pollEvent(event))
        if (event.type == sf::Event::Closed)
            window->close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window->close();
    if (!window->isOpen())
        exit(0);
    draw_cells(env, window);
    window->display();
    sf::sleep(sf::seconds(1./FPS));
    window->clear();
}
