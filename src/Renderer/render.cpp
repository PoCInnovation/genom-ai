#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>
#include "simulation_parameters.hpp"
#include "genome.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "environnement.hpp"

using namespace std;

static void draw_cells(Environnement &env, sf::RenderWindow *window, int grid_width, int grid_height)
{
    sf::CircleShape shape(min(grid_width, grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y) / 2);

    shape.setFillColor(sf::Color::Green);
    for (Cell *cell : env.cell_list){
        shape.setPosition((cell->x * grid_width) / max(GRID_SIZE_X, GRID_SIZE_Y), (cell->y * grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y));
        window->draw(shape);
    }
}

static void draw_obstacles(Environnement &env, sf::RenderWindow *window, int grid_width, int grid_height)
{
    sf::CircleShape shape(min(grid_width, grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y) / 2);

    shape.setFillColor(sf::Color::Blue);
    for (int i = 0; i < GRID_SIZE_X * GRID_SIZE_Y; i++) {
        if (env.obstacle_list[i] == true){
            shape.setPosition(((i % GRID_SIZE_X) * grid_width) / max(GRID_SIZE_X, GRID_SIZE_Y), (((int)i / GRID_SIZE_X) * grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y));
            window->draw(shape);
        }
    }
}

static void draw_info(string info, int y, sf::Text text, sf::RenderWindow *window)
{
    text.setString(info);
    text.setPosition(WINDOW_SIZE_X - 480, y);
    window->draw(text);
}

static void draw_wall(Environnement &env, sf::RenderWindow *window, int grid_width, int grid_height)
{
    sf::CircleShape shape(min(grid_width, grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y) / 2);

    shape.setFillColor(sf::Color::Red);
    if (GRID_SIZE_Y < GRID_SIZE_X) {
        for (int x = 0; x < GRID_SIZE_X; x++) {
            shape.setPosition((x * grid_width) / max(GRID_SIZE_X, GRID_SIZE_Y), (GRID_SIZE_Y * grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y));
            window->draw(shape);
        }
    }
    if (GRID_SIZE_X < GRID_SIZE_Y) {
        for (int y = 0; y < GRID_SIZE_Y; y++) {
            shape.setPosition((GRID_SIZE_X * grid_width) / max(GRID_SIZE_X, GRID_SIZE_Y), (y * grid_height) / max(GRID_SIZE_X, GRID_SIZE_Y));
            window->draw(shape);
        }
    }
}

static void draw_separation_line(sf::RenderWindow *window)
{
    sf::RectangleShape separation_line = sf::RectangleShape(sf::Vector2f(5, WINDOW_SIZE_Y));

    separation_line.setPosition(WINDOW_SIZE_X - 500, 0);
    separation_line.setFillColor(sf::Color(255, 255, 255, 255));
    window->draw(separation_line);
}

static string get_path_relative_to_this_file(string relative_path)
{
    string sourceDir = __FILE__;
    sourceDir = sourceDir.substr(0, sourceDir.find_last_of("/\\"));
    return sourceDir + "/" + relative_path;
}

static void draw_window(Environnement &env, sf::RenderWindow *window, int gen_number)
{
    sf::Font font;
    sf::Text text = sf::Text();

    font.loadFromFile(get_path_relative_to_this_file("../RobotoMono-Medium.ttf"));
    text.setFont(font);
    text.setCharacterSize(25);
    draw_info("Actual gen:       " + to_string(gen_number), 15, text, window);
    draw_info("World size:       " + to_string(GRID_SIZE_X) + "x" + to_string(GRID_SIZE_Y), 85, text, window);
    draw_info("Population:       " + to_string(CELL_COUNT), 125, text, window);
    draw_info("Steps/gen:        " + to_string(STEP_PER_GEN), 165, text, window);
    draw_info("Number of genes:  " + to_string(GENOME_LENGTH), 205, text, window);
    draw_info("Mutation chance:  " + to_string((float)MUTATION_CHANCE/100) + "%", 245, text, window);
    draw_separation_line(window);
    draw_wall(env, window, WINDOW_SIZE_X - 500, WINDOW_SIZE_Y);
    draw_cells(env, window, WINDOW_SIZE_X - 500, WINDOW_SIZE_Y);
    draw_obstacles(env, window, WINDOW_SIZE_X - 500, WINDOW_SIZE_Y);
}

void render(Environnement &env, sf::RenderWindow *window, int gen_number)
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
    draw_window(env, window, gen_number);
    window->display();
    sf::sleep(sf::seconds(1./FPS));
    window->clear();
}
