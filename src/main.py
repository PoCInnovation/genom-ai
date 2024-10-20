from utils import SimulationParameters, Vector2D
from Environment.environment import Environment
from Cell.cell import Cell
import multiprocessing
import time



def main(params):
    env = Environment(params)
    cell_list = [Cell(env) for _ in range(params.cell_count)]
    actual_gen = 0
    
    while True:
        env.clear_map()
        for cell in cell_list:
            env.add_cell_to_random_pos(cell)
        for actual_step in range(params.step_per_gen):
            pipe_broken = env.render(actual_gen, actual_step)
            if pipe_broken:
                print("pipe_broken (happen if you lose renderer window focus)(this error is temporary)(normally)")
                return
            for cell in cell_list:
                cell.process()
            time.sleep(0.1)
        actual_gen += 1



if __name__ == "__main__":
    params = SimulationParameters(
        size = Vector2D(10, 10),
        cell_count = 10,
        step_per_gen = 10,
    )
    
    process = multiprocessing.Process(target=exec, args=["import Renderer.renderer"])
    process.start()
    time.sleep(0.2)
    main(params)
    process.terminate()
