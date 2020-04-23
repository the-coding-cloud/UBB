"""
Task: solve a problem using Evolutionary Algorithm (EA), and a Hill Climbing Method:

For this lab, I have chosen a generational EA & the basic hill climbing method

Solution representation: list of 2*n permutations
"""
import numpy as np
import matplotlib.pyplot as plt
import random


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

        if self.currentState.fitness() == 0:
            print("SOLUTION FOUND:")
            print(self.currentState.getValues())

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

        return popFitness


class Controller:
    def __init__(self):
        pass

    def ea(self, n, population, mutation, iterations):
        evolutionaryAlg = EvolutionaryAlg(population, mutation, n)
        for i in range(iterations):
            evolutionaryAlg.iteration()

    def hc(self, n, iterations):
        individual = Individual()
        individual.generate(n)
        hillClimbing = HillClimbing(individual)
        for i in range(iterations):
            hillClimbing.iteration()

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


ctrl = Controller()
ctrl.runValidationTestEA(0.25, 4)
