import copy

class DirectedGraph:
    def __init__(self):
        '''
        Initialises an empty directed graph
        Contains:
            - number of vertices
            - number of edges
            - a list of vertices
            - a dictionary where:
                the key is a vertex 
                the value is a list of the predecessor vertices
            - a dictionary where:
                the key is a vertex
                the value is a list of the successor vertices
            - a dictionary where:
                the key is a (startVertex, endVertex) tuple representing an edge
                the value is the cost of the edge
        '''
        self.__vertices = 0
        self.__edges = 0
        self.__listOfVertices = []
        self.__dictIn = {}
        self.__dictOut = {}
        self.__dictCost = {}
        
    def loadFromFile(self, fileName):
        '''
        Function that loads a directed graph from a text file
        '''
        try:
            f = open(fileName, "r")
            
            line = f.readline().strip()
            aux = line.split(" ")
            self.__vertices = int(aux[0])
            self.__edges = int(aux[1])
            
            for index in range (0, self.__vertices):
                self.__dictIn[index] = []
                self.__dictOut[index] = []   
                self.__listOfVertices.append(index)
            
            line = f.readline().strip()
            while line != "":
                aux = line.split(" ")
                aux[0] = int(aux[0])
                aux[1] = int(aux[1])
                aux[2] = int(aux[2])
                
                self.addEdge(aux[0], aux[1], aux[2])
                
                line = f.readline().strip()
                
        except IOError:
            raise ValueError("Invalid input")
        finally:
            f.close()
    
    def getNumberOfVertices(self):
        '''
        Function that returns the number of vertices in the graph
        '''
        return self.__vertices
    
    def getNumberOfEdges(self):
        '''
        Function that returns the number of edges in the graph
        '''
        return self.__edges
        
    def getAllVertices(self):
        '''
        Function that returns a list with all the vertices
        '''
        return self.__listOfVertices
                
    def isEdge(self, startVertex, endVertex):
        '''
        Function that checks the existence of an edge
        Returns True if the edge exists
                False otherwise
        Input: startVertex, endVertex - integers
        Output: True/False
        Preconditions: startVertex, endVertex are vertices of the graph
        Postconditions: the function returns a boolean value
        '''
        if (startVertex, endVertex) in list(self.__dictCost.keys()):
            return True
        else:
            return False
        
    def isVertex(self, vertex):
        '''
        Function that checks whether a vertex is in the graph.
        Returns True if the vertex exists
                False otherwise
        Input: vertex - integer
        Output: True/False
        Preconditions: -
        Postconditions: the function returns a boolean value
        '''        
        if vertex in self.getAllVertices():
            return True
        else:
            return False 
        
    def getIndegree(self, vertex):
        '''
        Function that returns the indegree of a vertex
        Input: vertex - integer
        Output: indegree of the vertex
        Preconditions: the vertex is part of the graph
        Postconditions: the value returned is an integer representing the indegree
                        throws exception if the vertex is inexistent
        '''
        if self.isVertex(vertex):
            return len(self.__dictIn[vertex])
        else:
            raise ValueError("Inexistent vertex")
        
    def getOutdegree(self, vertex):
        '''
        Function that returns the outdegree of a vertex
        Input: vertex - integer
        Output: outdegree of the vertex
        Preconditions: the vertex is part of the graph
        Postconditions: the value returned is an integer representing the outdegree
                        throws exception if the vertex is inexistent
        '''
        if self.isVertex(vertex):
            return len(self.__dictOut[vertex])
        else:
            raise ValueError("Inexistent vertex")
        
    def getInboundVertices(self, vertex):
        '''
        Function that returns the inbound vertices for a vertex
        Input: vertex - integer
        Output: list of inbound vertices for a given vertex
        Preconditions: the vertex is part of the graph
        Postconditions: returns a list of inbound vertices for a given vertex
                        throws exception if the vertex is inexistent
        '''
        if self.isVertex(vertex):
            return copy.deepcopy(self.__dictIn[vertex])
        else:
            raise ValueError("Inexistent vertex")
        
    def getOutboundVertices(self, vertex):
        '''
        Function that returns the outbound vertices for a vertex
        Input: vertex - integer
        Output: list of outbound vertices for a given vertex
        Preconditions: the vertex is part of the graph
        Postconditions: returns a list of outbound vertices for a given vertex
                        throws exception if the vertex is inexistent
        '''
        if self.isVertex(vertex):
            return copy.deepcopy(self.__dictOut[vertex])
        else:
            raise ValueError("Inexistent vertex")
        
    def getEdgeCost(self, startVertex, endVertex):
        '''
        Function that returns the cost of a given edge
        Input: startVertex, endVertex - integers
        Output: edgeCost - integer
        Preconditions: the vertices are part of the graph/the edge exists
        Postconditions: returns the cost of the edge determined by the given vertices
                        throws exception if the edge is inexistent
        '''
        if self.isEdge(startVertex, endVertex):
            return self.__dictCost[(startVertex, endVertex)]
        else:
            raise ValueError("Invalid input - the edge does not exist")
        
    def modifyEdgeCost(self, startVertex, endVertex, newCost):
        '''
        Function that modifies the cost of a given edge
        Input: startVertex, endVertex, newCost - integers
        Output: edgeCost = newCost
        Preconditions: the vertices are part of the graph/the edge exists
        Postconditions: the function modifies the cost of the edge
                        throws exception if the edge is inexistent
        '''
        if self.isEdge(startVertex, endVertex):
            self.__dictCost[(startVertex, endVertex)] = newCost
        else:
            raise ValueError("Invalid input - the edge does not exist")
        
    def addEdge(self, startVertex, endVertex, edgeCost):
        '''
        Function that adds a new edge
        Input: startVertex, endVertex, edgeCost - integers
        Output: -
        Preconditions: the vertices are part of the graph/the edge does not exist
        Postconditions: the new edge is added
                        throws exception if the vertices are inexistent/the edge exists
        '''
        if not self.isEdge(startVertex, endVertex)\
        and self.isVertex(startVertex)\
        and self.isVertex(endVertex):
            self.__dictOut[startVertex].append(endVertex)
            self.__dictIn[endVertex].append(startVertex)
            self.__dictCost[(startVertex, endVertex)] = edgeCost
            self.__edges += 1
            
        else:
            raise ValueError("Invalid input - the edge already exists")
        
    def addVertex(self, vertex):
        '''
        Function that adds a new vertex
        Input: vertex - integer
        Output: -
        Preconditions: the vertex does not already exist
        Postconditions: the new vertex is added to the graph
                        throws exception if the vertex already exists
        '''
        if not self.isVertex(vertex):
            self.__dictIn[vertex] = []
            self.__dictOut[vertex] = []
            self.__vertices += 1
            self.__listOfVertices.append(vertex)
            
        else:
            raise ValueError("Invalid input - the vertex already exists")
        
    def removeEdge(self, startVertex, endVertex):
        '''
        Function that removes an edge
        Input: startVertex, endVertex - integers
        Output: -
        Preconditions: the vertices are part of the graph/the edge already exists
        Postconditions: the edge is removed
                        throws exception if the edge does not exist
        '''
        if self.isEdge(startVertex, endVertex):
            del self.__dictCost[(startVertex, endVertex)]
            self.__dictIn[endVertex].remove(startVertex)
            self.__dictOut[startVertex].remove(endVertex)
            self.__edges -= 1
            
        else:
            raise ValueError("Invalid input - inexistent edge")
        
    def removeVertex(self, vertex):
        '''
        Function that removes a vertex
        Input: vertex - integer
        Output: -
        Preconditions: the vertex is part of the graph
        Postconditions: the vertex is removed
                        throws exception if the vertex does not already exist
        '''
        if self.isVertex(vertex):
            outbound = self.getOutboundVertices(vertex)
            inbound = self.getInboundVertices(vertex)
            
            for endVertex in outbound:
                self.removeEdge(vertex, endVertex)
            del self.__dictOut[vertex]
                
            for startVertex in inbound:
                self.removeEdge(startVertex, vertex)
            del self.__dictIn[vertex]
                
            self.__vertices -= 1
            self.__listOfVertices.remove(vertex)
        else:
            raise ValueError("Invalid input - inexistent vertex")
        
    def copyGraph(self):
        '''
        Function that returns the copy of a graph
        '''
        return copy.deepcopy(self)
            
    def printGraph(self):
        print (list(self.__dictIn.keys()))
        print (list(self.__dictOut.keys()))
        print (list(self.__dictCost.keys()))
        
        for i in self.__listOfVertices:
            if len(self.__dictIn[i]) == len(self.__dictOut[i]) == 0:
                print(i, "- isolated vertex")
            else:
                print(i, ":", [j for j in self.__dictOut[i]])
        