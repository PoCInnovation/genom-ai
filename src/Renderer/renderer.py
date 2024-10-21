from pyglet.text import Label
from pyglet.shapes import Rectangle, Circle
from pyglet.graphics import Batch
import pyglet
import socket
import json
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import SimulationParameters, Vector2D, convert_dict_to_params



def receive_dict() -> dict:
    host = 'localhost'
    port = 61245
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        conn, _ = s.accept()
        with conn:
            data = conn.recv(1024)
            if data:
                return json.loads(data.decode('utf-8'))



class WindowSimulation(pyglet.window.Window):
    def __init__(self, size: Vector2D) -> None:
        super(WindowSimulation, self).__init__(size.x, size.y)
        self.window_size = size
        self.batch = None
    
    def on_draw(self) -> None:
        input_dict = receive_dict()
        map = input_dict["map"]
        params = convert_dict_to_params(input_dict["params"])
        map_size = params.size
        
        base_grid_pos = Vector2D(100, 150)
        base_grid_size = Vector2D(500, 500)
        if map_size.x < map_size.y:
            base_grid_size.x /= map_size.y/map_size.x
        elif map_size.y < map_size.x:
            base_grid_size.y /= map_size.x/map_size.y
        
        window.clear()
        batch = Batch()
        background = Rectangle(0, 0, width=window_size.x, height=window_size.y, color=(140, 140, 140), batch=batch)
        map_rectangle = Rectangle(base_grid_pos.x, window_size.y - base_grid_pos.y, width=base_grid_size.x, height=-base_grid_size.y, color=(190, 190, 190), batch=batch)
        
        shape_list = []
        for y in range(map_size.y):
            for x in range(map_size.x):
                if map[y][x] == 1:
                    cell_x = base_grid_pos.x + ((x+0.5)/map_size.x*base_grid_size.x)
                    cell_y = window_size.y - (base_grid_pos.y + ((y+0.5)/map_size.y*base_grid_size.y))
                    radius = min(base_grid_size.x/map_size.x/2, base_grid_size.y/map_size.y/2)
                    shape_list.append(Circle(cell_x, cell_y, radius=radius, color=(25, 200, 15), batch=batch))
        
        label_info = Label(f"Gen {input_dict['actual_gen']}", x = base_grid_pos.x + base_grid_size.x/2, y = window_size.y - (base_grid_pos.y - 30), color = (0, 0, 0), font_size=28, anchor_x="center")
        label_params = self.create_label_params(640, 630, params)
        
        background.draw()
        map_rectangle.draw()
        batch.draw()
        label_info.draw()
        label_params.draw()

    def create_label_params(self, x: float, y: float, params: SimulationParameters) -> Label:
        text = (
            f"World size:\t\t{params.size.x}x{params.size.y}\n"
            f"Population:\t\t{params.cell_count}\n"
            f"Steps/gen:\t\t{params.step_per_gen}\n"
        )
        return Label(text, x, y, multiline=True, width=400, color=(0, 0, 0), font_size=20)



window_size = Vector2D(1000, 800)
window = WindowSimulation(window_size)



pyglet.app.run()
