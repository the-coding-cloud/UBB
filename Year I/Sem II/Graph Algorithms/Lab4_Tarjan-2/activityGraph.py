from directedGraph import DirectedGraph

class Activity:
    def __init__(self, activityID, cost):
        self.activityID = activityID
        self.duration = cost
        self.earliestStart = 0
        self.latestStart = 0
        self.earliestEnd = 0
        self.latestEnd = 0
        
    def __eq__(self, other):
        return self.activityID == other.activityID
    def __str__(self):
        return str(self.activityID) + ' ' + str(self.duration) + ' ' + str(self.earliestStart) + ' ' + str(self.latestStart) + ' ' + str(self.earliestEnd) + ' ' + str(self.latestEnd)

class ActivityGraph:
    def __init__(self, start, end):
        self.graph = DirectedGraph()
        self.__activities = []
        self.__sortedActivities = []
        self.__criticalActivities = []
        self.start = start
        self.end = end
        self.graph.addVertex(start)
        self.graph.addVertex(end)

    def addActivity(self, a):
        self.__activities.append(a)

    def DepthFirst(self, sortedVertices, inStack, x):
        inStack.append(x)
        for y in self.graph.getOutboundVertices(x):
            if y not in inStack:
                if self.DepthFirst(sortedVertices, inStack, y) == False:
                    return False
            elif y in inStack and y not in sortedVertices:
                return False
        sortedVertices.append(x)
        
        return True

    def CheckIfDAG(self):
        inStack = []
        isDag = self.DepthFirst(self.__sortedActivities, inStack, self.start)
        if isDag == False:
            return isDag

        print(self.__sortedActivities)
        self.ComputeCriticalActivities()
            
        return isDag
    
    def ComputeCriticalActivities(self):
        for a in reversed(self.__sortedActivities):
            maxVal = 0
            inbound = []
            for v in self.graph.getInboundVertices(a):
                V = Activity(v, 0)
                inbound.append(V)
            for A in self.__activities:
                if A in inbound:
                    maxVal = max(maxVal, A.earliestEnd)
            A = Activity(a, 0)
            for activity in self.__activities:
                if activity == A:
                    activity.earliestStart = maxVal
                    activity.earliestEnd = maxVal + activity.duration

        for a in self.__sortedActivities:
            minVal = 99999999
            outbound = []
            for v in self.graph.getOutboundVertices(a):
                V = Activity(v, 0)
                outbound.append(V)
            for A in self.__activities:
                if A in outbound:
                    minVal = min(minVal, A.latestStart)
            A = Activity(a, 0)
            for activity in self.__activities:
                if activity == A:
                    activity.latestEnd = minVal
                    activity.latestStart = minVal - activity.duration
                    if activity.activityID == 'Y':
                        activity.latestEnd = activity.earliestEnd
                        activity.latestStart = activity.earliestStart
                    if activity.latestStart == activity.earliestStart:
                        self.__criticalActivities.append(activity)

    
    def GetActivities(self):
        return self.__activities
    
    def GetCriticalActivities(self):
        return self.__criticalActivities


while True:
    
    f = open("testInput.txt", "r")


    numberOfActivities = int(f.readline())
    activityGraph = ActivityGraph('X', 'Y') 
    
    a = Activity('X', 0)
    activityGraph.addActivity(a)
    a = Activity('Y', 0)
    activityGraph.addActivity(a)

    
    prerequisites = {}
    
    for i in range(numberOfActivities):
        line = f.readline().strip().split()
        activityID = line[0]
        duration = int(line[1])
        
        activityGraph.graph.addVertex(activityID)
        
        a = Activity(activityID, duration)
        activityGraph.addActivity(a)

        if line[2] == "-":
            prerequisites[activityID] = []
        else:
            prerequisites[activityID] = line[2].split(",")
        
        if len(prerequisites[activityID]) == 0:
            activityGraph.graph.addEdge('X', activityID, 0)
        
    for v in activityGraph.graph.getAllVertices():
        if v != activityGraph.end and v != activityGraph.start:
            for x in prerequisites[v]:
                activityGraph.graph.addEdge(x, v, 0)
                
    for v in activityGraph.graph.getAllVertices():
        if v != activityGraph.end and len(activityGraph.graph.getOutboundVertices(v)) == 0:
            activityGraph.graph.addEdge(v, 'Y', 0)

    break

def printMenu():

    print("1 - Check If DAG")
    print("2 - Print Activities")
    print("3 - Print Critical Activities")
    print("0 - Exit")

def CheckIfDAG():
    print(activityGraph.CheckIfDAG())

def PrintActivities():
    totalTime = 0
    for a in activityGraph.GetActivities():
        if a.activityID == 'X' or a.activityID == 'Y':
            if a.activityID == 'Y':
                totalTime = a.latestEnd
            continue
        print(a)

    print("Total project time: ", totalTime)

def PrintCriticalActivities():
    for a in activityGraph.GetCriticalActivities():
        if a.activityID == 'X' or a.activityID == 'Y':
            continue
        print(a.activityID, end=" ")
        
    print()

while(True):
    printMenu()
    try:
        command = int(input("Enter command: "))
    except:
        continue
    
    functions = {1:CheckIfDAG, 2:PrintActivities, 3:PrintCriticalActivities}

    if command == 0:
        break
    elif command in functions.keys():
        #try:
        functions[command]()
        #except Exception as e:
        #    print(e)
