#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "environnement.hpp"
#include "render.hpp"
#include "cell.hpp"
#include "loop.hpp"


using namespace std;

int gene_to_int(Gene gene)
{
    int int_gene = 0;

    for (int i = gene.size() - 1; i > 0; i--)
        int_gene += (gene[GEN_LENGTH - i - 1] << i);
    return int_gene;
}

Gene int_to_gene(int int_gene)
{
    Gene gene = {0};

    for (int i = 0; i < GEN_LENGTH; i++)
        gene[GEN_LENGTH - i - 1] = (bool)(int_gene & (1 << i));
    return gene;
}

ofstream get_save(string filename)
{
    struct stat folder_info;

    if (stat("../save", &folder_info) != 0)
        mkdir("../save", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return ofstream("../save/" + filename);
}

int save_gen(Environnement &env)
{
    ofstream file = get_save("save_gen.txt");

    for (int i = 0; i < env.cell_list.size(); i++) {
        for (int j = 0; j < env.cell_list[i]->genome.gen_list.size(); j++) {
            file << gene_to_int(env.cell_list[i]->genome.gen_list[j]);
            if (j != env.cell_list[i]->genome.gen_list.size() - 1)
                file << " ";
        }
        if (i != env.cell_list.size() - 1)
            file << "\n";
    }
    file.close();
    return 0;
}

vector<Cell *> load_cell(string filename)
{
    array<Gene, GENOME_LENGTH> gene_list = {};
    vector<Cell *> cell_list = {};
    std::ifstream file("../save/" + filename);
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

#if REPLAY_MODE
int main()
{
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "SFML works!");
    Environnement env = Environnement();
    vector<Cell *> cell_list;

    cell_list = load_cell("save_gen.txt");
    while (1) {
        for (Cell *cell : cell_list)
            env.add_cell_to_rand_pos(cell);
        for (int j = 0; j < STEP_PER_GEN; j++){
            compute_step(env);
            render(env, &window, 0);
        }
        for (int y = 0; y < GRID_SIZE_Y; y++)
            for (int x = 0; x < GRID_SIZE_X; x++)
                SET_ENV_CELL(&env, nullptr, x, y);
    }
    return 0;
}
#endif