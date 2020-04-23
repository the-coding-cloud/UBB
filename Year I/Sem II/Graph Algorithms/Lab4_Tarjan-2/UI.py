from controller import Controller


class Console(object):
    def __init__(self, controller):
        assert isinstance(controller, Controller)
        self.__controller = controller

    def UIGetNumberOfVertices(self):
        '''
        Function that returns the number of vertices
        '''
        print(self.__controller.getNumberOfVertices())
        
    def UIGetNumberOfEdges(self):
        '''
        Function that returns the number of edges
        '''
        print(self.__controller.getNumberOfEdges())

    def UIParseAllVertices(self):
        '''
        Function that parses the graph and prints the vertices
        '''
        print(self.__controller.parseAllVertices())

    def UIIsEdge(self):
        '''
        Function that checks the existence of an edge
        '''
        try:
            startVertex = int(input("Start vertex: ").strip())
            endVertex = int(input("End vertex: ").strip())
            print(self.__controller.isEdge(startVertex, endVertex))
        except ValueError as ve:
            print(ve)
            
    def UIIsVertex(self):
        '''
        Function that checks the existence of a vertex
        '''
        try:
            vertex = int(input("Vertex: ").strip())
            print(self.__controller.isVertex(vertex))
        except ValueError:
            print("Invalid input")

    def UIGetInDegree(self):
        '''
        Function that the in degree of a given vertex
        '''
        try:
            vertex = int(input("Vertex: ").strip())
            degree = self.__controller.getIndegree(vertex)
            print("In degree is: " + str(degree))
        except ValueError as ve:
            print(ve)

    def UIGetOutDegree(self):
        '''
        Function that the out degree of a given vertex
        '''
        try:
            vertex = int(input("Vertex: ").strip())
            degree = self.__controller.getOutdegree(vertex)
            print("Out degree is: " + str(degree))
        except ValueError as ve:
            print(ve)

    def UIParseOutboundEdges(self):
        '''
        Function that parses the out bound edges of a given vertex
        '''
        try:
            vertex = int(input("Vertex: ").strip())
            print(self.__controller.getOutboundVertices(vertex))
        except ValueError as ve:
            print(ve)

    def UIParseInboundEdges(self):
        '''
        Function that parses the in bound edges of a given vertex
        '''
        try:
            vertex = int(input("Vertex: ").strip())
            print(self.__controller.getInboundVertices(vertex))
        except ValueError as ve:
            print(ve)

    def UIModifyEdgeCost(self):
        '''
        Function that modifies the information associated to a given edge and modifies that value
        '''
        try:
            startVertex = int(input("Start vertex of the edge: ").strip())
            endVertex = int(input("End vertex of the edge: ").strip())
            edgeCost = int(input("New cost of the edge: ").strip())
            self.__controller.modifyEdgeCost(startVertex, endVertex, edgeCost)
            print("Edge cost has been successfully modified!")

        except ValueError as ve:
            print(ve)

    def UIRetrieveEdgeCost(self):
        '''
        Function that retrieves the information associated to a given edge and modifies that value
        '''
        try:
            startVertex = int(input("Start vertex of the edge: ").strip())
            endVertex = int(input("End vertex of the edge: ").strip())
            print("Edge cost is: " + str(self.__controller.getEdgeCost(startVertex, endVertex)))
        except ValueError as ve:
            print(ve)

    def UIAddEdge(self):
        '''
        Function that adds a new edge(from startVertex to endVertex) with the cost associated to it, cost
        '''
        try:
            startVertex = int(input("Start vertex of the edge: ").strip())
            endVertex = int(input("End vertex of the edge: ").strip())
            edgeCost = int(input("Cost of the edge: ").strip())
            self.__controller.addEdge(startVertex, endVertex, edgeCost)
            print("Edge has been successfully added!")
        except ValueError as ve:
            print(ve)

    def UIRemoveEdge(self):
        '''
        Function that removes a given edge(from firstVertex to secondVertex)
        '''
        try:
            startVertex = int(input("Start vertex of the edge: ").strip())
            endVertex = int(input("End vertex of the edge: ").strip())
            self.__controller.removeEdge(startVertex, endVertex)
            print("Edge has been successfully removed!")
        except ValueError as ve:
            print(ve)

    def UIAddVertex(self):
        '''
        Function that adds a new vertex to the graph
        '''
        try:
            vertex = int(input("New vertex: ").strip())
            self.__controller.addVertex(vertex)
            print("Vertex has been successfully added!")
        except ValueError as ve:
            print(ve)

    def UIRemoveVertex(self):
        '''
        Function that removes a given vertex from the graph(it also removes the edges containing it)
        '''
        try:
            vertex = int(input("Vertex to remove: ").strip())
            self.__controller.removeVertex(vertex)
            print("Vertex has been successfully removed!")
        except ValueError as ve:
            print(ve)

    def UIListGraph(self):
        '''
        Function that copies the edges of the directed graph
        '''
        self.__controller.printGraph()

    def printMenu(self):
        print("1. Get the number of vertices")
        print("2. Get the number of edges")
        print("3. Parse the set of vertices")
        print("4. Check the existence of an edge")
        print("5. Check the existence of a vertex")
        print("6. Get the in degree of a vertex")
        print("7. Get the out degree of a vertex")
        print("8. Parse the set of out bound edges of a certain vertex")
        print("9. Parse the set of in bound edges of a certain vertex")
        print("10. Retrieve cost of a certain edge")
        print("11. Modify cost of a certain edge")
        print("12. Add an edge")
        print("13. Remove an edge")
        print("14. Add a vertex")
        print("15. Remove a vertex")
        print("16. Print graph")
        print("17. Exit")

    def run(self):
        commands = {
                    "1": self.UIGetNumberOfVertices,
                    "2": self.UIGetNumberOfEdges,
                    "3": self.UIParseAllVertices,
                    "4": self.UIIsEdge,
                    "5": self.UIIsVertex,
                    "6": self.UIGetInDegree,
                    "7": self.UIGetOutDegree,
                    "8": self.UIParseOutboundEdges,
                    "9": self.UIParseInboundEdges,
                    "10": self.UIRetrieveEdgeCost,
                    "11": self.UIModifyEdgeCost,
                    "12": self.UIAddEdge,
                    "13": self.UIRemoveEdge,
                    "14": self.UIAddVertex,
                    "15": self.UIRemoveVertex,
                    "16": self.UIListGraph
                    }
        self.printMenu()

        while True:
            try:
                x = input("Please choose a valid command: ")
                if x == "17":
                    return
                if x in commands.keys():
                    commands[x]()
                else:
                    print("Invalid command, try again.")
            except ValueError as v:
                print(v)


