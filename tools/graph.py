import random
import time
from dataclasses import dataclass

import igraph as ig
import matplotlib.pyplot as plt

@dataclass
class NeuronLink :
    inputType : bool
    inputIndex : int
    outputType : bool
    outputIndex : int
    weight : int

gen_lenght = 4
input_neuron_list = ["X_POS","Y_POS","CONST_1","CONST_0","CONST_MINUS_1","CONST_HALF","CONST_MINUS_HALF"]
output_neuron_list = ["X_MOV", "Y_MOV"]
layer_size = 3
layer_neuron_list = ["Layer " + i.__str__() for i in range(layer_size)]

neuron_list = input_neuron_list + layer_neuron_list + output_neuron_list
def binaryListToInt(binlist: list[int]) -> int:
    result: int = 0
    for i in binlist:
        result = (result << 1) + i
    return result


def genToBinaryList(gen: int) -> list[int]:
    return [int(bit) for bit in bin(gen)[2:]]

def indextype(index : int, type_neuron : bool, is_input : bool):
    if is_input:
        if type_neuron == 0:
            return index % len(input_neuron_list)
        return len(input_neuron_list) + index % len(layer_neuron_list)
    if type_neuron == 0:
        return len(input_neuron_list) + index % len(layer_neuron_list)
    return len(input_neuron_list) + len(layer_neuron_list) + index % len(output_neuron_list)

random.seed(time.time())

class Genome:
    genome: list[list[int]]

    def __init__(self, intgenome: list[int] = None):
        if intgenome is None:
            self.genome = [[random.randint(0, 1) for _ in range(32)] for _ in range(gen_lenght)]
        else :
            self.genome = [genToBinaryList(gen) for gen in intgenome]

    def genomeToNeuronLinkList(self):
        return [NeuronLink(gen[0] == 1, binaryListToInt(gen[1:8]), gen[8] == 1, binaryListToInt(gen[9:16]),
                           binaryListToInt(gen[16:])) for gen in self.genome]

links = Genome().genomeToNeuronLinkList()

edges = [(indextype(x.inputIndex , x.inputType, True), indextype(x.outputIndex, x.outputType, False)) for x in links]

n_vertices = len(neuron_list)
g = ig.Graph(n_vertices, edges, directed=True)

g.vs["name"] = neuron_list
g.vs["type"] = ["input" for _ in range(len(input_neuron_list))] + ["layer" for _ in range(layer_size)]+ ["output" for _ in range(len(output_neuron_list))]
g.es["weight"] = [link.weight / pow(2, 15) for link in links]
fig, ax = plt.subplots(figsize=(n_vertices,n_vertices))


ig.plot(
    g,
    target=ax,
    layout="fruchterman_reingold", # print nodes in a circular layout
    vertex_size=90,
    vertex_color=["#4682B4" if neuron_type == "layer" else "#FF0000" if neuron_type == "output" else "#32CD32" for neuron_type in g.vs["type"]],
    vertex_frame_width=4.0,
    vertex_frame_color="white",
    vertex_label=g.vs["name"],
    vertex_label_size=20.0,
    edge_width=[weight for weight in g.es["weight"]],
    edge_color="#7142cf"
)

plt.show()
