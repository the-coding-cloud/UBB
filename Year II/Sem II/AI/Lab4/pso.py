"""
Task: solve a problem using Particle Swarm Optimisation.

Solution representation: list of 2*n permutations
"""
import numpy as np
import matplotlib.pyplot as plt
from itertools import permutations


class Particle:
    def __init__(self, size):
        self.position = []
        self.size = size
        self.generate(size)
        self.fit = self.fitness()
        self.bestPos = self.position[:]
        self.bestFitness = self.fit
        self.velocity = [0 for i in range(size * 2)]

    def generate(self, n):
        self.size = n
        for i in range(2 * n):
            perm = np.random.permutation([i for i in range(1, n + 1)])
            self.position.append(tuple(perm))

    def fitness(self):
        fitness = 0

        # fitness = 0 : solution
        # For each duplicate pair & each column & line that is not a permutation, we increment fitness

        pairs = []

        for i in range(self.size):
            columnS = []
            columnT = []
            for j in range(self.size):
                pairs.append((self.position[j][i], self.position[j + self.size][i]))
                columnS.append(self.position[j][i])
                columnT.append(self.position[j + self.size][i])

            if len(columnS) > len(set(columnS)):
                fitness += 1
            if len(columnT) > len(set(columnS)):
                fitness += 1

        fitness += len(pairs) - len(set(pairs))
        return fitness

    def setValues(self, values):
        self.position = values
        self.size = len(values) // 2

    def getValues(self):
        return self.position[:]

    def setVelocity(self, velocity):
        self.velocity = velocity

    def getVelocity(self):
        return self.velocity

    def setPosition(self, position):
        self.position = position

    def getPosition(self):
        return self.position

    def setBestPosition(self, position):
        self.bestPos = position

    def getBestPosition(self):
        return self.bestPos

    def setBestFitness(self, fitness):
        self.bestFitness = fitness

    def getBestFitness(self):
        return self.bestFitness


class PSO:
    def __init__(self, particleSize, popSize, nbhdSize, c1, c2, w):
        self.population = [Particle(particleSize) for i in range(popSize)]
        self.neighbourhoods = []
        self.particleSize = particleSize
        self.c1 = c1
        self.c2 = c2
        self.w = w
        self.popSize = popSize
        self.nbhdSize = nbhdSize
        self.generateNeighbours()
        self.permutationList = list(permutations([i for i in range(1, self.particleSize + 1)]))

    def generateNeighbours(self):
        if self.nbhdSize > self.popSize:
            self.nbhdSize = self.popSize

        self.neighbourhoods = []
        for i in range(self.popSize):
            currentNeighbours = []
            for j in range(self.nbhdSize):
                x = np.random.randint(0, self.popSize - 1)
                while x in currentNeighbours:
                    x = np.random.randint(0, self.popSize - 1)
                currentNeighbours.append(x)
            self.neighbourhoods.append(currentNeighbours)

    def iteration(self):
        for i in range(self.popSize):
            # Find best neighbour
            bestNeighbour = self.neighbourhoods[i][0]
            for j in range(self.nbhdSize):
                if self.population[bestNeighbour].fitness() < self.population[self.neighbourhoods[i][j]].fitness():
                    bestNeighbour = j

            # Compute new velocity

            currentVelocity = self.population[i].getVelocity()
            newVelocity = [0 for i in range(self.particleSize * 2)]

            for k in range(self.particleSize * 2):
                r1 = np.random.random()
                r2 = np.random.random()

                newVelocity[k] = self.w * currentVelocity[k]
                + self.c1 * r1 * (self.permutationList.index(self.population[bestNeighbour].getPosition()[k]) - self.permutationList.index(self.population[i].getPosition()[k]))
                + self.c2 * r2 * (self.permutationList.index(self.population[i].getBestPosition()[k]) - self.permutationList.index(self.population[i].getPosition()[k]))

            self.population[i].setVelocity(newVelocity)

            # Compute new position
            newPosition = []
            for k in range(self.particleSize * 2):
                permIndex1 = self.permutationList.index(self.population[i].getPosition()[k])
                permIndex2 = newVelocity[k]
                newPosition.append(self.permutationList[int(permIndex1 + permIndex2) % len(self.permutationList)])

            self.population[i].setPosition(newPosition)

            # Update memory
            if self.population[i].fitness() < self.population[i].getBestFitness():
                self.population[i].setBestPosition(newPosition)
                self.population[i].setBestFitness(self.population[i].fitness())

            if self.population[i].fitness() == 0:
                print(self.population[i])

        self.w *= 0.99

        return self.population[:]


class Controller:
    def __init__(self):
        pass

    def pso(self, n, popSize, nbhdSize, w, c1, c2, iterations):
        alg = PSO(n, popSize, nbhdSize, c1, c2, w)
        for i in range(iterations):
            alg.iteration()
            print("Iteration", i)


ctrl = Controller()
ctrl.pso(3, 20, 10, 1.5, 1, 2, 30)
