from dataclasses import dataclass

@dataclass
class NeuronLink :
    inputType : int
    inputIndex : int
    outputType : int
    outputIndex : int
    weight : int