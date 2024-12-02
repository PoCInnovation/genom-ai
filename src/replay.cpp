// #include <iostream>
// #include <vector>
// #include "simulation_parameters.hpp"
// #include "render.hpp"
// #include "cell.hpp"
// #include "environnement.hpp"
// #include "die.hpp"
// #include "reproduction.hpp"
// #include "print_progress_bar.hpp"

// using namespace std;    

// static void compute_cells(Environnement &env, Cell *cell)
// {
//     const vector<float> inputs = {((((float)cell->x)/((float)GRID_SIZE_X))-0.5f)*2.0f, ((((float)cell->y)/((float)GRID_SIZE_Y))-0.5f)*2.0f, 1, 0, -1, 0.5, -0.5};

//     const array<float, OUTPUT_SIZE> brain_output = cell->brain.forward_cell(inputs);

//     env.move_cell(cell, static_cast<int>(brain_output[0]), static_cast<int>(brain_output[1]));
// }

// static int compute_step(Environnement &env)
// {
//     for (Cell *cell : env.cell_list)
//         compute_cells(env, cell);
//     return 0;
// }

// static int compute_gen(Environnement &env, sf::RenderWindow *window, int gen)
// {
//     for (int j = 0; j < STEP_PER_GEN; j++){
//         compute_step(env);
//         if (gen >= GEN_TO_START_RENDER)
//             render(env, window, gen);
//     }
//     return 0;
// }

// int loop(sf::RenderWindow *window)
// {
//     Environnement env = Environnement();

//     for (int gen = 0; gen < MAX_GEN; gen++){
//         if (gen == 0){
//             for (int j = 0; j < CELL_COUNT; j++)
//                 env.create_cell_to_rand_pos();
//         } else {
//             apply_die_rule(env);
//             reproduce_cells(env);
//         }
//         if (gen == GEN_TO_START_RENDER && RENDER)
//             window = new sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
//         compute_gen(env, window, gen);
//         if (gen < GEN_TO_START_RENDER)
//             print_progress_bar(((float)gen)/((float)GEN_TO_START_RENDER));
//     }
//     return 0;
// }

// int replay_gen()
// {

// }

// int main()
// {
//     replay_gen();
// }



#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include "environnement.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "loop.hpp"


using namespace std;

int gene_to_int(Gene gene)
{
    int int_gene = 0;
    int i = gene.size() - 1;

    for (bool bit : gene) {
        int_gene += bit << i;
        i--;
    }
    return int_gene;
}

Gene int_to_gene(int int_gene)
{
    Gene gene = {0};

    for (int i = 0; i < GEN_LENGTH; i++)
        gene[GEN_LENGTH - i - 1] = (bool)(int_gene & (1 << i));
    return gene;
}

int save_gen(Environnement &env)
{
    ofstream file("../save_gen.txt");

    for (Cell *cell : env.cell_list) {
        for (Gene &gene : cell->genome.gen_list){
            file << gene_to_int(gene) << " ";
        }
        file << "\n";
    }
    file.close();
    return 0;
}

vector<Cell *> load_cell(string filename)
{
    array<Gene, GENOME_LENGTH> gene_list = {};
    vector<Cell *> cell_list = {};
    std::ifstream file(filename);
    std::string line;
    int num;

    while (std::getline(file, line)) {
        std::istringstream line_stream(line);
        for (int i = 0; line_stream >> num; i++)
            gene_list[i] = int_to_gene(num);
        cell_list.push_back(new Cell(0, 0, Genome(gene_list)));
    }
    file.close();
    return cell_list;
}

#if REPLAY_MODE == true
int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
    Environnement env = Environnement();
    vector<Cell *> cell_list;

    cell_list = load_cell("../save_gen.txt");
    for (Cell *cell : cell_list)
        env.add_cell_to_rand_pos(cell);
    for (int j = 0; j < STEP_PER_GEN; j++){
        compute_step(env);
        render(env, &window, 0);
    }
    return 0;
}
#endif