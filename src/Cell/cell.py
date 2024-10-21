from utils import Vector2D
from Environment.environment import Environment



class Cell:
    def __init__(self, env: Environment, pos = Vector2D(0, 0)) -> None:
        self.env = env
        self.pos = pos
    
    def process(self) -> None:
        self.env.move_cell(self.pos, self.pos + Vector2D(1, 0))
