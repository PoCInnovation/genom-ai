from PySide6.QtWidgets import QApplication, QMainWindow, QLabel, QHBoxLayout, QListWidget, QWidget
from PySide6.QtGui import QPixmap
from PySide6.QtCore import Qt
from igraph.drawing.utils import BoundingBox
from igraph.drawing import Plot
from graph import get_graph, Genome
from dataclasses import dataclass
import tempfile
import sys
import os



SAVE_FILENAME = "../../save/save_gen.txt"
GRAPH_SCALE = 0.5
PLOT_SIZE = 800, 600



@dataclass
class Cell:
    name: str
    genome: Genome


class CellListWidget(QListWidget):
    def __init__(self, parent, save_filename):
        super().__init__(parent)
        
        self.parent_window = parent
        with open(save_filename, "r") as f:
            genes = [tuple(map(int, line.split(" "))) for line in f.read().split("\n")]
        genes_dict = {str(gene):[gene, genes.count(gene)] for gene in set(genes)}
        self.cell_list = [Cell(f"Gene {i+1}   {count}/{len(genes)}", Genome(gene)) for i, (gene, count) in enumerate(sorted(genes_dict.values(), key=lambda x:x[1], reverse=True))]
        self.insertItems(0, (cell.name for cell in self.cell_list))
        self.currentRowChanged.connect(self.new_cell_selected)
    
    def new_cell_selected(self, index):
        self.parent_window.generate_and_display_graph(self.cell_list[index].genome)


class GraphWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("igraph with PyQt")
        self.resize(1000, 800)

        self.central_widget = QWidget()
        self.setCentralWidget(self.central_widget)
        self.main_layout = QHBoxLayout(self.central_widget)
        
        self.graph_label = QLabel(self)
        self.graph_label.setAlignment(Qt.AlignCenter)
        self.main_layout.addWidget(self.graph_label)

        self.cell_list_widget = CellListWidget(self, SAVE_FILENAME)
        self.main_layout.addWidget(self.cell_list_widget)

    def generate_and_display_graph(self, genome):
        g = get_graph(genome)

        temp_file = tempfile.NamedTemporaryFile(suffix=".png", delete=False)
        temp_file.close()
        
        plot = Plot(temp_file.name, bbox=(PLOT_SIZE[0], PLOT_SIZE[1]))
        plot.add(
            g,
            bbox=BoundingBox(PLOT_SIZE[0]*0.1, PLOT_SIZE[1]*0.1, PLOT_SIZE[0]*0.9, PLOT_SIZE[1]*0.9),
            layout="fruchterman_reingold",
            vertex_size=90*GRAPH_SCALE,
            vertex_color=["#4682B4" if neuron_type == "layer" else "#FF0000" if neuron_type == "output" else "#32CD32" for neuron_type in g.vs["type"]],
            vertex_frame_width=4.0*GRAPH_SCALE,
            vertex_frame_color="white",
            vertex_label=g.vs["name"],
            vertex_label_size=20.0*GRAPH_SCALE,
            edge_width=g.es["weight"],
            edge_color="#7142cf"
        )
        plot.redraw()
        plot.save()

        pixmap = QPixmap(temp_file.name)
        self.graph_label.setPixmap(pixmap)
    
    def keyPressEvent(self, event):
        if event.key() == Qt.Key.Key_Escape:
            self.close()



if __name__ == "__main__":
    if not os.path.exists(SAVE_FILENAME):
        print(f"{SAVE_FILENAME} does not exist")
        exit(1)
    app = QApplication(sys.argv)
    window = GraphWindow()
    window.show()
    sys.exit(app.exec())
