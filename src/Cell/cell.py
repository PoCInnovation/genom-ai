from utils import Vector2D



class Cell:
    def __init__(self, env, pos = Vector2D(0, 0)):
        self.env = env
        self.pos = pos
    
    def process(self):
        self.env.move_cell(self.pos, self.pos + Vector2D(1, 0))
