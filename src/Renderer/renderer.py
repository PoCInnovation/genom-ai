import pyglet
import socket
import json
import sys
import os

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from utils import Vector2D



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
        map_size = input_dict["size"]
        map_size = Vector2D(map_size[0], map_size[1])
        
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
                    shape_list.append(pyglet.shapes.Circle(base_grid_pos.x + ((x+0.5)/map_size.x*base_grid_size.x), window_size.y - (base_grid_pos.y + ((y+0.5)/map_size.y*base_grid_size.y)), radius=min(base_grid_size.x/map_size.x/2, base_grid_size.y/map_size.y/2), color=(25, 200, 15), batch=batch))
        batch.draw()



window_size = Vector2D(800, 800)
window = WindowSimulation(window_size)



pyglet.app.run()
