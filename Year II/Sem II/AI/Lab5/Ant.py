import numpy as np
from copy import deepcopy


class Ant:
    def __init__(self, n):
        self.values = None
        self.size = n
        self.startAnt()

    def startAnt(self):
        # Simultaneously initialize the first position in each permutation in the permutation list (solution representation)
        # with valid column permutations (condition for valid solutions) - at least start with something correct...
        self.values = [[] for i in range(2 * self.size)]

        perm = np.random.permutation([i for i in range(1, self.size + 1)])
        for i in range(self.size):
            self.values[i].append(perm[i])

        perm = np.random.permutation(perm)
        for i in range(self.size):
            self.values[i + self.size].append(perm[i])

    def evaluate(self):
        fitness = 1

        # fitness = 0 : solution
        # For each duplicate pair & each column that is not a permutation, we increment fitness

        pairs = []
        for i in range(self.size):
            columnS = []
            columnT = []
            for j in range(self.size):
                pairs.append((self.values[j][i], self.values[j + self.size][i]))
                columnS.append(self.values[j][i])
                columnT.append(self.values[j + self.size][i])

            if len(columnS) > len(set(columnS)):
                fitness += 1
            if len(columnT) > len(set(columnS)):
                fitness += 1

        fitness += len(pairs) - len(set(pairs))
        return fitness

    def computeDistance(self, values):
        # Computes 1 + the number of errors from a set of values (duplicate values)
        pairs = []

        for i in range (self.size):
            for j in range(self.size):
                if i < len(self.values[j]) and i < len(self.values[j + self.size]):
                    pairs.append((self.values[j][i], self.values[j + self.size][i]))

        distance = 1 + len(pairs) - len(set(pairs))
        return distance

    def nextMove(self, trace, alpha, beta, q0):
        # Generates the next elements in the permutations

        for k in range(len(self.values)):
            visited = self.values[k]
            total = [i for i in range(1, self.size + 1)]
            valid = list(set(total).difference(set(visited)))

            i = self.values[k][-1] - 1
            p = []
            for j in valid:
                newValues = deepcopy(self.values)
                newValues[k].append(j)
                prob = (trace[k][i][j - 1] ** alpha) * (self.computeDistance(newValues) ** beta)

                p.append(prob)

            totalProb = sum(p)

            if totalProb != 0:
                for j in range(len(valid)):
                    p[j] = p[j] / totalProb

                if np.random.random() < q0:
                    selection = []
                    for j in range(len(valid)):
                        selection.append([valid[j], p[j]])
                    j = max(selection, key=lambda a: a[1])
                    self.values[k].append(j[0])

                else:
                    j = np.random.choice(valid, size=1, replace=True, p=p)
                    self.values[k].append(j[0])

            else:
                j = np.random.choice(valid)
                self.values[k].append(j)

    def getValues(self):
        return self.values
