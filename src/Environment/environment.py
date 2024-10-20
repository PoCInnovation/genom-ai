from random import randint
from utils import Vector2D
import socket
import json



def send_dict(data):
    host = 'localhost'
    port = 61245
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(json.dumps(data).encode('utf-8'))
        return False
    except ConnectionError:
        return True



class Environment:
    def __init__(self, size, cell_count):
        self.size = size
        self.cell_count = cell_count
        self.map = [[None for _ in range(self.size.x)] for _ in range(self.size.y)]
    
    def add_cell(self, cell, pos):
        self.map[pos.y][pos.x] = cell
        cell.pos = pos
        
    def add_cell_to_random_pos(self, cell):
        pos = Vector2D(randint(0, self.size.x - 1), randint(0, self.size.y - 1))
        while self.is_pos_full(pos):
            pos = Vector2D(randint(0, self.size.x - 1), randint(0, self.size.y - 1))
        self.add_cell(cell, pos)
    
    def get_cell(self, pos):
        return self.map[pos.y][pos.x]
    
    def move_cell(self, start_pos, end_pos):
        if self.is_pos_free(end_pos):
            self.add_cell(self.get_cell(start_pos), end_pos)
            self.remove_cell(start_pos)
    
    def remove_cell(self, pos):
        self.map[pos.y][pos.x] = None
    
    def is_out_off_bound(self, pos):
        return pos.x >= self.size.x or pos.x < 0 or pos.y >= self.size.y or pos.y < 0
    
    def is_pos_full(self, pos):
        if self.is_out_off_bound(pos):
            return True
        return self.map[pos.y][pos.x] is not None
    
    def is_pos_free(self, pos):
        return not self.is_pos_full(pos)
    
    def clear_map(self):
        self.map = [[None for _ in range(self.size.x)] for _ in range(self.size.y)]

    def render(self):
        # convert objects to json-proof objects
        return send_dict({
            "map": [[1 if self.map[y][x] is not None else 0 for x in range(self.size.x)] for y in range(self.size.y)],
            "size": [self.size.x, self.size.y]
        })
