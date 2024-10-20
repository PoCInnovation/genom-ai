import pyglet
import socket
import json
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import Vector2D, convert_dict_to_params



def receive_dict():
    host = 'localhost'
    port = 61245
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((host, port))
        s.listen()
        conn, addr = s.accept()
        with conn:
            data = conn.recv(1024)
            if data:
                return json.loads(data.decode('utf-8'))



class WindowSimulation(pyglet.window.Window):
    def __init__(self, size):
        super(WindowSimulation, self).__init__(size.x, size.y)
        self.window_size = size
        self.batch = None
    
    def on_draw(self):
        input_dict = receive_dict()
        map = input_dict["map"]
        params = convert_dict_to_params(input_dict["params"])
        map_size = params.size
        
        base_grid_pos = Vector2D(200, 200)
        base_grid_size = Vector2D(400, 400)
        if map_size.x < map_size.y:
            base_grid_size.x /= map_size.y/map_size.x
        elif map_size.y < map_size.x:
            base_grid_size.y /= map_size.x/map_size.y
        
        window.clear()
        batch = pyglet.graphics.Batch()
        shape_list = []
        shape_list.append(pyglet.shapes.Rectangle(base_grid_pos.x, window_size.y - base_grid_pos.y, width=base_grid_size.x, height=-base_grid_size.y, color=(120, 120, 120), batch=batch))
        for y in range(map_size.y):
            for x in range(map_size.x):
                if map[y][x] == 1:
                    cell_x = base_grid_pos.x + ((x+0.5)/map_size.x*base_grid_size.x)
                    cell_y = window_size.y - (base_grid_pos.y + ((y+0.5)/map_size.y*base_grid_size.y))
                    radius = min(base_grid_size.x/map_size.x/2, base_grid_size.y/map_size.y/2)
                    shape_list.append(pyglet.shapes.Circle(cell_x, cell_y, radius=radius, color=(25, 200, 15), batch=batch))
        batch.draw()



window_size = Vector2D(800, 800)
window = WindowSimulation(window_size)



pyglet.app.run()
