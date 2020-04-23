from undirectedGraph import UndirectedGraph

graph = UndirectedGraph()
graph.loadFromFile("input.txt")

partialResult = set()
excludedCandidates = set()
candidates = graph.getAllVertices()
graph.getCliqueVertices(partialResult, candidates, excludedCandidates)