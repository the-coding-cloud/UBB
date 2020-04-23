from directedGraph import DirectedGraph
from controller import Controller
from UI import Console

graph = DirectedGraph()
graph.loadFromFile("graph1k.txt")

controller = Controller(graph)
console = Console(controller)

console.run()