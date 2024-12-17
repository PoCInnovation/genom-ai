#ifndef SIMULATION_PARAMETERS_HPP
#define SIMULATION_PARAMETERS_HPP

#define CELL_COUNT 200
#define GRID_SIZE_X 100
#define GRID_SIZE_Y 100

#define MAX_GEN 3001
#define STEP_PER_GEN 500
#define SAVE_EVERY_X_GEN 300

#define FPS 300
#define RENDER true
#define GEN_TO_START_RENDER 2996
#define REPLAY_MODE false
#define SAVE_FOLDER_PATH "../../save"

#define MUTATION_CHANCE 500 // value is chance over 10 000, so 100 is 1%
#define RANDOM_NEW_CELL_CHANCE 500 // value is chance over 10 000, so 100 is 1%
#define ONE_PARENT true
#define RANDOM_PARENT false
#define RANDOM_REPRODUCE true

#define GENOME_LENGTH 32
#define GEN_LENGTH 32

#define LAYER_NEURON_LENGTH 16

#endif
