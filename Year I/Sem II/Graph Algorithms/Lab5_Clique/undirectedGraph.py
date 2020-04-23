import copy

class UndirectedGraph:
    def __init__(self):
        self.__dictIn = {}
        self.__dictOut = {}
        self.__vertices = 0
        self.__edges = 0
        self.__listOfVertices = []
        self.__maximumClique = 0
        self.__done = 0
        
    def loadFromFile(self, fileName):
        '''
        Function that loads an undirected graph from a text file
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
                
                self.addEdge(aux[0], aux[1])
                
                line = f.readline().strip()
                
        except IOError:
            raise ValueError("Invalid input")
        finally:
            f.close()
            
    def isEdge(self, startVertex, endVertex):
        '''
        Function that checks the existence of an edge
        '''
        if startVertex in self.__dictIn[endVertex]:
            return True
        else:
            return False
        
    def isVertex(self, vertex):
        if vertex in self.__listOfVertices:
            return True
        else:
            return False
            
    def addEdge(self, startVertex, endVertex):
        '''
        Function that adds a new edge
        '''
        if not self.isEdge(startVertex, endVertex):
            self.__dictIn[startVertex].append(endVertex)
            self.__dictIn[endVertex].append(startVertex)
            self.__dictOut[startVertex].append(endVertex)
            self.__dictOut[endVertex].append(startVertex)
            
            self.__dictIn[startVertex].sort()
            self.__dictIn[endVertex].sort()
            self.__dictOut[startVertex].sort()
            self.__dictOut[endVertex].sort()
            
        else:
            pass
        
    def addVertex(self, vertex):
        if not self.isVertex(vertex):
            self.__dictIn[vertex] = []
            self.__dictOut[vertex] = []
            self.__listOfVertices.append(vertex)
        else:
            print ("vertex exists")

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
        
    def getDegree(self, vertex):
        '''
        Function that returns the degree of a vertex
        '''
        return len(self.__dictIn[vertex])
        
    def getAllVertices(self):
        '''
        Function that returns a list with all the vertices
        '''
        return self.__listOfVertices
    
    def getInboundVertices(self, vertex):
        '''
        Function that returns the in bound vertices for a given vertex
        '''
        return copy.deepcopy(self.__dictIn[vertex])
    
    def getOutboundVertices(self, vertex):
        '''
        Function that returns the out bound vertices for a given vertex
        '''
        return copy.deepcopy(self.__dictOut[vertex])
    
    def bfs(self, startVertex):
        queue = [startVertex]
        visited = [startVertex]
        while queue:  
            node = queue.pop(0)
            neighbours = self.getOutboundVertices(node)
    
            for neighbour in neighbours:
                if neighbour not in visited:
                    queue.append(neighbour)
                    visited.append(neighbour)
        return visited
    
    def getConnectedComponents(self):
        visited = []
        for vertex in self.getAllVertices():
            visited.append(False)
            
        solution = []
    
        for vertex in self.getAllVertices():
            if not visited[vertex]:
                result = self.bfs(vertex)
                subgraph = self.getConnectedComponent(result)
                solution.append(subgraph)
                for visitedVertex in result:
                    visited[visitedVertex] = True
                    
        return solution
    
    def getConnectedComponent(self, vertices):
        subgraph = UndirectedGraph()
        subgraph.__vertices = len(vertices)
        subgraph.__listOfVertices = vertices
        
        edges = 0
        
        for vertex in vertices:
            subgraph.__dictIn[vertex] = self.__dictIn[vertex]
            subgraph.__dictOut[vertex] = self.__dictOut[vertex]
            edges += len(self.__dictIn[vertex])
            
        subgraph.__edges = edges
        
        return subgraph
    
    def getCliqueVertices(self, partialResult, candidates, excludedCandidates):
        if len(candidates) == 0 and len(excludedCandidates) == 0:
            print(len(partialResult))
            print(partialResult)
            self._done = 1
            exit(0)
        else:
            if self.__done > 0:
                return 
            else:
                for v in candidates:
                    if self.__done > 0:
                        return 
                    partialResult.add(v)
                    np = set()
                    nx = set()
                    for i in self.getOutboundVertices(v):
                        if i in candidates:
                            np.add(i)
                        elif i in excludedCandidates:
                            nx.add(i)
                    if self.__done > 0:
                        return
                    else: 
                        self.getCliqueVertices(partialResult, np, nx)
                        candidates.remove(v)
                        excludedCandidates.add(v)
    '''
    def clique(self, neighbours, size):
        if len(neighbours) == 0:
            if size > self.__maximumClique:
                self.__maximumClique = size
            return 
        while len(neighbours) > 0:
            if size + len(neighbours) <= self.__maximumClique:
                return
            else:
                i = 0
                for j in range(0, self.getNumberOfVertices()):
                    if j in neighbours:
                        i = j
                        break
                neighbours.remove(i)
                newNeighbours = set()
                for j in self.getOutboundVertices(i):
                    if self.getDegree(j)>= self.__maximumClique:
                        if j in neighbours:
                            newNeighbours.add(j)
                            
                self.clique(newNeighbours, size + 1)
                
        
    def findMaxClique(self):
        self.__maximumClique = 0
        
        for i in range(1, int(self.getNumberOfVertices())):
            if self.getDegree(i) >= self.__maximumClique:
                u = set()
                for j in self.getOutboundVertices(i):
                    if j > i:
                        if self.getDegree(j) >= self.__maximumClique:
                            u.add(j)
                self.clique(u, 1) 
          
        print("Maximum clique size is " + str(self.__maximumClique))  
        
            
        partialResult = set()
        excludedCandidates = set()
        candidates = self.getAllVertices()
        self.getCliqueVertices(partialResult, candidates, excludedCandidates)
    '''
    def printGraph(self):
        for i in self.getAllVertices():
            if len(self.__dictIn[i]) == len(self.__dictOut[i]) == 0:
                print(i, ":", self.__dictOut[i])
            else:
                print(i, ":", [j for j in self.__dictOut[i]])