from undirectedGraph import UndirectedGraph

graph = UndirectedGraph()
graph.loadFromFile("input.txt")

connectedComponents = graph.getConnectedComponents()

for component in connectedComponents:
    component.printGraph()
    print("----------")
    
connectedComponents