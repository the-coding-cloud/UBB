import numpy as np
import math


class Repository:
    def __init__(self, filePath):
        self.filePath = filePath
        self.x = None
        self.y = None

    def readData(self):
        with open(self.filePath, "r") as file:
            x = []
            y = []
            for line in file:
                if line != "\n":
                    x.append([float(1)])  # Corresponds to the constant
                    inputs = list(map(float, line.strip(" ").split(" ")))
                    output = inputs.pop()
                    x[-1].extend(inputs)
                    y.append(output)

        self.x = x
        self.y = y


class ProblemController:
    def __init__(self, repo, learningRate, maxError):
        self.repository = repo
        self.learningRate = learningRate
        self.beta = None
        self.n = len(self.repository.y)
        self.m = len(self.repository.x[0])
        self.maxError = maxError

    def generateRandomCoefficients(self):
        self.beta = np.random.rand(6)

    def descendingGradientAlg(self):
        avgErrors = []
        coefficients = []
        i = 1
        avgError = 1000000000

        while avgError > self.maxError:
            print("iteration: ", i)
            i += 1

            computedOutputs = []
            for row in range(self.n):
                # Compute f(x)
                computedOutput = 0
                for col in range(self.m):
                    computedOutput += self.repository.x[row][col] * self.beta[col]

                computedOutputs.append(computedOutput)

            errors = []
            for row in range(self.n):
                # Error = computedOutput - realOutput
                errors.append(computedOutputs[row] - self.repository.y[row])

            for col in range(self.m):
                # Adjust the coefficients
                aux = 0
                for row in range(self.n):
                    aux += self.repository.x[row][col] * errors[row]

                self.beta[col] = self.beta[col] - (self.learningRate / self.n) * aux

            avgError = math.sqrt(1 / self.n * sum([error ** 2 for error in errors]))
            avgErrors.append(avgError)

            coefficients.append(self.beta)

        return coefficients[-1], avgErrors


class Console:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        self.controller.generateRandomCoefficients()
        beta, avgErrors = self.controller.descendingGradientAlg()

        print(avgErrors[-1])
        print(beta)


repo = Repository("db.txt")
repo.readData()
problem = ProblemController(repo, 0.0001, 0.4)
console = Console(problem)
console.run()

