from directedGraph import DirectedGraph

class Controller:
    def __init__(self, graph):
        assert isinstance(graph, DirectedGraph)
        self.__graph = graph

    def addVertex(self, newVertex):
        self.__graph.addVertex(newVertex)

    def addEdge(self, startVertex, endVertex, cost):
        self.__graph.addEdge(startVertex, endVertex, cost)

    def isEdge(self, startVertex, endVertex):
        if self.isVertex(startVertex) and self.isVertex(endVertex):
            return self.__graph.isEdge(startVertex, endVertex)
        else:
            raise ValueError("Invalid input - inexistent vertices")
        
    def isVertex(self, vertex):
        return self.__graph.isVertex(vertex)

    def modifyEdgeCost(self, startVertex, endVertex, newCost):
        self.__graph.modifyEdgeCost(startVertex, endVertex, newCost)

    def removeEdge (self, startVertex, endVertex):
        self.__graph.removeEdge(startVertex, endVertex)

    def removeVertex(self, vertex):
        self.__graph.removeVertex(vertex)

    def getEdgeCost(self, startVertex, endVertex):
        return self.__graph.getEdgeCost(startVertex, endVertex)

    def getNumberOfVertices(self):
        return self.__graph.getNumberOfVertices()
    
    def getNumberOfEdges(self):
        return self.__graph.getNumberOfEdges()

    def getIndegree(self, vertex):
        return self.__graph.getIndegree(vertex)

    def getOutdegree(self, vertex):
        return self.__graph.getOutdegree(vertex)

    def parseAllVertices(self):
        return self.__graph.getAllVertices()

    def printGraph(self):
        self.__graph.printGraph()

    def getInboundVertices(self, vertex):
        return self.__graph.getInboundVertices(vertex)

    def getOutboundVertices(self, vertex):
        return self.__graph.getOutboundVertices(vertex)
    
    def Dijkstra(self, startVertex, endVertex):
        if self.isVertex(startVertex) and self.isVertex(endVertex):
            return self.__graph.Dijkstra(startVertex, endVertex)
        else:
            raise ValueError("Invalid input - inexistent vertices")