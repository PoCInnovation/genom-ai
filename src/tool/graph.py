from dataclasses import dataclass, field
import matplotlib.pyplot as plt
import igraph as ig
import random
import time



random.seed(time.time())
LAYER_SIZE = 32
INPUT_NEURON_LIST = ["X_POS","Y_POS","CONST_1","CONST_0","CONST_MINUS_1","CONST_HALF","CONST_MINUS_HALF","CROWD_TOP","CROWD_RIGHT","CROWD_BOT","CROWD_LEFT", "FOOD_BAR", "WATER_BAR"]
LAYER_NEURON_LIST = [f"Layer {i}" for i in range(LAYER_SIZE)]
OUTPUT_NEURON_LIST = ["X_MOV", "Y_MOV"]
NEURON_LIST = INPUT_NEURON_LIST + LAYER_NEURON_LIST + OUTPUT_NEURON_LIST
NEURON_TYPE_LIST = ["input"] * len(INPUT_NEURON_LIST) + ["layer"] * len(LAYER_NEURON_LIST) + ["output"] * len(OUTPUT_NEURON_LIST)



@dataclass
class NeuronLink:
    input_type: bool
    input_index: int
    output_type: bool
    output_index: int
    weight: int
    
    def get_input_index(self):
        if self.input_type == 0:
            return self.input_index % len(INPUT_NEURON_LIST)
        return len(INPUT_NEURON_LIST) + self.input_index % len(LAYER_NEURON_LIST)
    
    def get_output_index(self):
        if self.output_type == 0:
            return len(INPUT_NEURON_LIST) + self.output_index % len(LAYER_NEURON_LIST)
        return len(INPUT_NEURON_LIST) + len(LAYER_NEURON_LIST) + self.output_index % len(OUTPUT_NEURON_LIST)


class Genome:
    genome: list[list[int]]

    def __init__(self, intgenome: list[int]):
        self.genome = [int_to_bit_list(gen) for gen in intgenome]

    def to_neuron_link_list(self):
        return [NeuronLink(gen[0] == 1, bit_list_to_int(gen[1:8]), gen[8] == 1, bit_list_to_int(gen[9:16]),
                           bit_list_to_int(gen[16:])) for gen in self.genome]


@dataclass
class Node:
    name: str
    type: str
    index: int
    input: list['Node'] = field(default_factory=list)
    input_weight: list[int] = field(default_factory=list)
    output: list['Node'] = field(default_factory=list)
    output_weight: list[int] = field(default_factory=list)
    
    def add_input(self, data, weight):
        if not any(data is existing for existing in self.input):
            self.input.append(data)
            self.input_weight.append(weight)

    def add_output(self, data, weight):
        if not any(data is existing for existing in self.output):
            self.output.append(data)
            self.output_weight.append(weight)



def bit_list_to_int(binlist: list[int]) -> int:
    result: int = 0
    for i in binlist:
        result = (result << 1) + i
    return result


def int_to_bit_list(gen: int) -> list[int]:
    return [int(bit) for bit in f"{gen:032b}".replace("-", "")]


def parcour(node: Node, memory: list, node_list_to_draw: list, weight_list: list, edges: list):
    end_with_input = False
    
    if node.type == "input":
        return True
    
    for input, weight in zip(node.input, node.input_weight):
        if input not in memory:
            if parcour(input, memory + [node], node_list_to_draw, weight_list, edges):
                end_with_input = True
                if input not in node_list_to_draw:
                    node_list_to_draw.append(input)
                if node not in node_list_to_draw:
                    node_list_to_draw.append(node)
                edges.append((node_list_to_draw.index(input), node_list_to_draw.index(node)))
                weight_list.append(weight / pow(2, 15))
    
    return end_with_input


def get_graph(genome: Genome):
    links = genome.to_neuron_link_list()
    
    node_list = [Node(NEURON_LIST[i], NEURON_TYPE_LIST[i], i) for i in range(len(NEURON_LIST))]
    for link in links:
        if link.get_input_index() == link.get_output_index():
            continue
        node_list[link.get_input_index()].add_output(node_list[link.get_output_index()], link.weight)
        node_list[link.get_output_index()].add_input(node_list[link.get_input_index()], link.weight)
    
    node_list_to_draw = []
    weight_list = []
    edges = []
    for node in node_list:
        if node.type == "output":
            parcour(node, [], node_list_to_draw, weight_list, edges)
    
    vertices_count = len(node_list_to_draw)
    g = ig.Graph(vertices_count, edges, directed=True)
    g.vs["name"] = [node.name for node in node_list_to_draw]
    g.vs["type"] = [node.type for node in node_list_to_draw]
    g.es["weight"] = weight_list
    
    return g



if __name__ == "__main__":
    genome = Genome()
    links = genome.to_neuron_link_list()

    edges = [(link.get_input_index(), link.get_output_index()) for link in links]

    vertices_count = len(NEURON_LIST)
    
    g = ig.Graph(vertices_count, edges, directed=True)
    g.vs["name"] = NEURON_LIST
    g.vs["type"] = NEURON_TYPE_LIST
    g.es["weight"] = [link.weight / pow(2, 15) for link in links]
    fig, ax = plt.subplots(figsize=(vertices_count,vertices_count))

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
        edge_width=g.es["weight"],
        edge_color="#7142cf"
    )

    plt.show()
