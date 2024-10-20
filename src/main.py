from Environment.environment import Environment
from Cell.cell import Cell
from utils import Vector2D
import multiprocessing
import time



def main(size, cell_count):
    env = Environment(size, cell_count)
    cell_list = [Cell(env) for _ in range(cell_count)]
    
    while True:
        env.clear_map()
        for cell in cell_list:
            env.add_cell_to_random_pos(cell)
        for _ in range(5):
            pipe_broken = env.render()
            if pipe_broken:
                print("pipe_broken (happen if you lose renderer window focus)(this error is temporary)(normally)")
                return
            for cell in cell_list:
                cell.process()
            time.sleep(0.1)



if __name__ == "__main__":
    process = multiprocessing.Process(target=exec, args=["import Renderer.renderer"])
    process.start()
    time.sleep(0.2)
    main(Vector2D(10, 10), 10)
    process.terminate()
