# Simple Vector, accept basic math operation (+, -, *, /) and print

class Vector2D:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, Vector2D):
            return Vector2D(self.x + other.x, self.y + other.y)
    __radd__ = __add__
    
    def __sub__(self, other):
        if isinstance(other, Vector2D):
            return Vector2D(self.x - other.x, self.y - other.y)
    __rsub__ = __sub__
    
    def __mul__(self, other):
        if isinstance(other, Vector2D):
            return Vector2D(self.x * other.x, self.y * other.y)
    __rmul__ = __mul__
    
    def __true_div__(self, other):
        if isinstance(other, Vector2D):
            return Vector2D(self.x / other.x, self.y / other.y)
    __rtrue_div__ = __true_div__
    
    def __repr__(self):
        return f"{{Vector2D x={self.x} y={self.y}}}"
