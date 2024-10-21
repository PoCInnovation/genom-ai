from dataclasses import dataclass



# Simple Vector, accept basic math operation (+, -, *, /) and print, accept both Vector2D(x, y) and Vector2D([x, y])
class Vector2D:
    def __init__(self, *args) -> None:
        if len(args) == 1 and isinstance(args[0], (list, tuple)) and len(args[0]) == 2:
            self.x, self.y = args[0]
        elif len(args) == 2:
            self.x, self.y = args
        else:
            raise ValueError("Vector2D requires either two values or a list/tuple of two elements.")

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
    
    def __repr__(self) -> str:
        return f"{{Vector2D x={self.x} y={self.y}}}"


@dataclass
class SimulationParameters:
    size: Vector2D
    cell_count: int
    step_per_gen: int



def convert_params_to_dict(params: SimulationParameters) -> dict:
    params_attr = [a for a in dir(params) if not a.startswith('__') and not callable(getattr(params, a))]
    dict_ = {attr: getattr(params, attr) for attr in params_attr}
    for key, val in dict_.items():
        if isinstance(val, Vector2D):
            dict_[key] = [val.x, val.y]
    return dict_


def convert_dict_to_params(dict_: dict) -> SimulationParameters:
    for key, val in dict_.items():
        if isinstance(val, (list, tuple)) and len(val) == 2:
            dict_[key] = Vector2D(val)
    return SimulationParameters(**dict_)
