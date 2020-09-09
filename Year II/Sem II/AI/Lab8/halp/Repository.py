class Repository:
    def __init__(self):
        self.data = []
        self.loadData()

    def loadData(self):
        file = open("datalab8.txt")
        for line in file:
            line = line.strip("\n")
            num = line.split(" ")
            n = [[], [], [], [], [], []]
            for i in range(len(num)):
                n[i] = float(num[i])
            self.data.append(n)
