from random import randint
from Cell.cell import Cell
from utils import Vector2D, SimulationParameters
from utils import convert_params_to_dict
import socket
import json



def send_dict(dict_: dict) -> bool:
    host = 'localhost'
    port = 61245
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))
            s.sendall(json.dumps(dict_).encode('utf-8'))
        return False
    except ConnectionError:
        return True



class Environment:
    def __init__(self, params: SimulationParameters) -> None:
        self.params = params
        self.size = params.size
        self.cell_count = params.cell_count
        self.map = [[None for _ in range(self.size.x)] for _ in range(self.size.y)]
    
    def add_cell(self, cell: Cell, pos: Vector2D) -> None:
        self.map[pos.y][pos.x] = cell
        cell.pos = pos
        
    def add_cell_to_random_pos(self, cell: Cell) -> None:
        pos = Vector2D(randint(0, self.size.x - 1), randint(0, self.size.y - 1))
        while self.is_pos_full(pos):
            pos = Vector2D(randint(0, self.size.x - 1), randint(0, self.size.y - 1))
        self.add_cell(cell, pos)
    
    def get_cell(self, pos: Vector2D) -> None:
        return self.map[pos.y][pos.x]
    
    def move_cell(self, start_pos: Vector2D, end_pos: Vector2D) -> None:
        if self.is_pos_free(end_pos):
            self.add_cell(self.get_cell(start_pos), end_pos)
            self.remove_cell(start_pos)
    
    def remove_cell(self, pos: Vector2D) -> None:
        self.map[pos.y][pos.x] = None
    
    def is_out_off_bound(self, pos: Vector2D) -> bool:
        return pos.x >= self.size.x or pos.x < 0 or pos.y >= self.size.y or pos.y < 0
    
    def is_pos_full(self, pos: Vector2D) -> bool:
        if self.is_out_off_bound(pos):
            return True
        return self.map[pos.y][pos.x] is not None
    
    def is_pos_free(self, pos: Vector2D) -> bool:
        return not self.is_pos_full(pos)
    
    def clear_map(self) -> None:
        self.map = [[None for _ in range(self.size.x)] for _ in range(self.size.y)]

    def render(self, actual_gen: int, actual_step: int) -> bool:
        # convert objects to json-proof objects
        return send_dict({
            "map": [[1 if self.map[y][x] is not None else 0 for x in range(self.size.x)] for y in range(self.size.y)],
            "params": convert_params_to_dict(self.params),
            "actual_gen": actual_gen,
            "actual_step": actual_step,
        })
