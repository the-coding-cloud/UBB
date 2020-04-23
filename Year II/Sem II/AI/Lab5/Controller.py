from Lab5.Problem import Problem
from Lab5.Ant import Ant

import numpy as np
from copy import deepcopy
import matplotlib.pyplot as plt


class Controller:
    def __init__(self, problem):
        '''
        constructor
        '''
        self.problem = problem
        self.noEpoch = None
        self.noAnts = None
        self.alpha = None
        self.beta = None
        self.rho = None
        self.q0 = None

    def loadParameters(self, filename):
        with open(filename, "r") as f:
            self.noEpoch = int(f.readline())
            self.noAnts = int(f.readline())
            self.alpha = float(f.readline())
            self.beta = float(f.readline())
            self.rho = float(f.readline())
            self.q0 = float(f.readline())

    def iteration(self, trace):
        antSet = [Ant(self.problem.n) for i in range(self.noAnts)]

        # Generate path
        for i in range(self.problem.n - 1):
            for ant in antSet:
                ant.nextMove(trace, self.alpha, self.beta, self.q0)

        # Update trace
        partialTrace = [[[0 for i in range(self.problem.n)] for j in range(self.problem.n)] for k in
                        range(2 * self.problem.n)]

        for ant in antSet:
            score = ant.evaluate()
            path = ant.getValues()
            for i in range(2 * self.problem.n):
                for j in range(self.problem.n - 1):
                    l = path[i][j] - 1
                    c = path[i][j + 1] - 1

                    partialTrace[i][l][c] += 1 / score

        # Update global trace
        for i in range(2 * self.problem.n):
            for j in range(self.problem.n):
                for k in range(self.problem.n):
                    trace[i][j][k] *= (1 - self.rho)
                    trace[i][j][k] += partialTrace[i][j][k]

        bestSol = max(antSet, key=lambda x: x.evaluate())

        return bestSol, trace

    def algorithm(self):
        trace = [[[0 for i in range(self.problem.n)] for j in range(self.problem.n)] for k in
                 range(2 * self.problem.n)]

        bestSol = None

        for i in range(self.noEpoch):
            bestSol, trace = self.iteration(trace)

        return bestSol
