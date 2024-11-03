from neuron_link import NeuronLink

class Genome :
    
    genome : list[list[int]]

    def __init__(self, genome : list[int]):
        self.genome = [self.genToBinaryList(gen) for gen in genome]

    def genToBinaryList(self, gen : int) -> list[int]:
      return [int(bit) for bit in bin(gen)[2:]]
    
    def binaryListToInt(self, list : list[int]) -> int:
        result : int = 0
        for i in list:
          result = (result << 1) + i
        return result
    
    def genomeToNeuronLinkList(self) :
       return [NeuronLink(gen[0], self.binaryListToInt(gen[1:8]), gen[8], self.binaryListToInt(gen[9:16]), self.binaryListToInt(gen[16:])) for gen in self.genome]

gens = [0x9ccc8807, 0x852cfdd3, 0x2304d598, 0xf1351fe3, 0xbdad817, 0xaea73b91, 0x90d7619a, 0x4b0bc470, 0x09db3cf7, 0x792140ee, 0x773a7333, 0xdae46757, 0x44982386, 0x2fee6766, 0x0ee35a30, 0xb3b4628f]
test = int("f1351fe3", 16)

genome = Genome(gens)
print(genome.genomeToNeuronLinkList())

