#include <vector>
#include <algorithm>
#include "cell.hpp"
#include "environnement.hpp"
#include "simulation_parameters.hpp"

static bool die_rule(Cell *cell)
{
    // die if not in the 25% left of the grid
    return cell->x > GRID_SIZE_X * 0.25;
}

void apply_die_rule(Environnement &env)
{
    // filter with the die rule
    env.cell_list.erase(remove_if(env.cell_list.begin(), env.cell_list.end(), die_rule), env.cell_list.end());
}
