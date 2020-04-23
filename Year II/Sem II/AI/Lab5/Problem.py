class Problem:
    def __init__(self, filename):
        '''
        constructor
        '''
        self.filename = filename
        self.n = None
        self.loadProblem()

    def loadProblem(self):
        '''
        read data from file
        '''
        with open(self.filename, "r") as f:
            self.n = int(f.readline())

