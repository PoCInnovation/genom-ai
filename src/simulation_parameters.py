from geometry import Vector2D
from dataclasses import dataclass



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
