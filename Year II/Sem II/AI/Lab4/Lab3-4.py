"""
Task: solve a problem using Particle Swarm Optimisation.

Solution representation: list of 2*n permutations
"""
import numpy as np
import matplotlib.pyplot as plt
import math
from itertools import permutations


class Individual:
    def __init__(self, elements=None):
        if elements is None:
            self.values = []
            self.size = None
        else:
            self.values = elements
            self.size = len(elements) // 2

    def generate(self, n):
        self.size = n
        for i in range(2 * n):
            perm = np.random.permutation([i for i in range(1, n + 1)])
            self.values.append(perm)

    def fitness(self):
        fitness = 0

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

    def setValues(self, values):
        self.values = values
        self.size = len(values) // 2

    def getValues(self):
        return self.values[:]


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
            if len(columnT) > len(set(columnT)):
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
                if self.population[bestNeighbour].fitness() > self.population[self.neighbourhoods[i][j]].fitness():
                    bestNeighbour = j

            # Compute new velocity

            currentVelocity = self.population[i].getVelocity()
            newVelocity = [0 for i in range(self.particleSize * 2)]

            if self.population[i].fitness() != 0:
                for k in range(self.particleSize * 2):
                    r1 = np.random.random()
                    r2 = np.random.random()

                    newVelocity[k] = self.w * currentVelocity[k] \
                                     + self.c2 * r1 * (self.permutationList.index(
                        self.population[bestNeighbour].getPosition()[k]) - self.permutationList.index(
                        self.population[i].getPosition()[k])) \
                                     + self.c1 * r2 * (self.permutationList.index(
                        self.population[i].getBestPosition()[k]) - self.permutationList.index(
                        self.population[i].getPosition()[k]))

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

            print(self.population[i].fitness())

            if self.population[i].fitness() == 0:
                print(self.population[i].getPosition())

        self.w *= 0.99

        return self.population[:]


class HillClimbing:
    def __init__(self, individual):
        self.initialState = individual
        self.currentState = individual

    def generateNeighbours(self):
        neighbours = []
        values = self.currentState.getValues()
        for i in range(len(values)):
            copyValues = values[:]
            copyValues[i] = np.random.permutation(copyValues[i])
            neighbour = Individual(copyValues)
            neighbours.append(neighbour)

        return neighbours

    def iteration(self):
        neighbours = self.generateNeighbours()
        neighbours.sort(key=lambda x: x.fitness())
        self.currentState = neighbours[0]

        return self.currentState

    def getCurrentState(self):
        return self.currentState


class EvolutionaryAlg:
    def __init__(self, populationSize, mutation, n):
        self.population = []
        self.n = n
        self.mutation = mutation
        for i in range(populationSize):
            individual = Individual()
            individual.generate(n)
            self.population.append(individual)

    def mutate(self, individual):
        if np.random.random() < self.mutation:
            values = individual.getValues()
            i = np.random.randint(0, self.n)
            values[i] = np.random.permutation(values[i])
            return Individual(values)
        else:
            return individual

    def crossover(self, individual1, individual2):
        # Chose to do a uniform crossover
        childValues = []
        firstParentValues = individual1.getValues()
        secondParentValues = individual2.getValues()

        for i in range(2 * self.n):
            if np.random.random() < 0.5:
                childValues.append(firstParentValues[i])
            else:
                childValues.append(secondParentValues[i])

        return Individual(childValues)

    def iteration(self):
        # Proportional selection
        probabilities = []
        maxFitness = 0
        popFitness = []

        for individual in self.population:
            f = individual.fitness()
            popFitness.append(f)
            if f > maxFitness:
                maxFitness = f

        sum2 = 0
        for f in popFitness:
            sum2 += maxFitness - f

        for f in popFitness:
            probabilities.append((maxFitness - f) / sum2)

        probabilities.sort(reverse=True)
        self.population.sort(key=lambda x: x.fitness())

        parent1, parent2 = np.random.choice(np.arange(len(self.population)), size=2, replace=False, p=probabilities)

        child = self.crossover(self.population[parent1], self.population[parent2])
        self.mutate(child)

        childFitness = child.fitness()
        parent1Fitness = self.population[parent1].fitness()
        parent2Fitness = self.population[parent2].fitness()

        # Elitism (survival selection)
        if parent1Fitness > parent2Fitness and parent1Fitness > childFitness:
            self.population[parent1] = child
        if parent2Fitness > parent1Fitness and parent2Fitness > childFitness:
            self.population[parent2] = child

        return self.population


class Controller:
    def __init__(self):
        pass

    def ea(self, n, population, mutation, iterations):
        evolutionaryAlg = EvolutionaryAlg(population, mutation, n)
        population = None
        for i in range(iterations):
            population = evolutionaryAlg.iteration()

        bestSolution = population[0]
        for i in range(len(population)):
            if bestSolution.fitness() > population[i].fitness():
                bestSolution = population[i]

        return bestSolution

    def hc(self, n, iterations):
        individual = Individual()
        individual.generate(n)
        hillClimbing = HillClimbing(individual)
        population = None
        for i in range(iterations):
            hillClimbing.iteration()

        bestSolution = population[0]
        for i in range(len(population)):
            if bestSolution.fitness() > population[i].fitness():
                bestSolution = population[i]

        return bestSolution

    def pso(self, n, popSize, nbhdSize, w, c1, c2, iterations):
        alg = PSO(n, popSize, nbhdSize, c1, c2, w)
        population = None
        for i in range(iterations):
            population = alg.iteration()

        bestSolution = population[0]
        for i in range(len(population)):
            if bestSolution.fitness() > population[i].fitness():
                bestSolution = population[i]

        return bestSolution

    def runValidationTestEA(self, mutation, n):
        res = []
        std = []
        avg = []

        for k in range(30):
            print("Iteration ", k)
            res.append([])
            evolutionaryAlg = EvolutionaryAlg(40, mutation, n)
            for i in range(1000):
                popFitness = evolutionaryAlg.iteration()
                res[k].append(min(popFitness))
            std.append(np.std(res[k]))
            avg.append(np.mean(res[k]))

        print(std)
        print(avg)

        std, = plt.plot(std, color='m', label='Std deviation')
        avg, = plt.plot(avg, color='y', label='Average')
        plt.legend(handles=[std, avg])
        plt.show()


class UI:
    def __init__(self):
        self.controller = Controller()

    def printMenu(self):
        print("0. Exit")
        print("1. HC")
        print("2. EA")
        print("3. PSO")
        print("4. Run validation tests")

    def run(self):
        self.printMenu()
        option = -1
        while option != 0:
            option = int(input("Pick an option:"))

            if option == 1:
                n = int(input("n: "))
                iterations = int(input("iterations: "))
                print(self.controller.hc(n, iterations))

            if option == 2:
                n = int(input("n: "))
                population = int(input("population: "))
                iterations = int(input("iterations: "))
                mutation = float(input("mutation: "))
                print(self.controller.ea(n, population, mutation, iterations))

            if option == 3:
                n = int(input("n: "))
                population = int(input("population: "))
                iterations = int(input("iterations: "))
                nbhd = int(input("neighbourhood size: "))
                w = float(input("w: "))
                c1 = float(input("c1: "))
                c2 = float(input("c2: "))

                print(self.controller.pso(n, population, nbhd, w, c1, c2, iterations))

            if option == 4:
                self.controller.runValidationTestEA(0.2, 4)
