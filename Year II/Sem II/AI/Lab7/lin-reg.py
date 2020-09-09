import numpy as np
import math


def readData(filePath):
    with open(filePath, "r") as file:
        x = []
        y = []
        for line in file:
            if line != "\n":
                x.append([float(1)])  # Corresponds to the constant
                inputs = list(map(float, line.strip(" ").split(" ")))
                output = inputs.pop()
                x[-1].extend(inputs)
                y.append(output)

    return x, y


def descendingGradient(x, y, beta, learningRate, maxError):
    avgErrors = []
    coefficients = []
    n = len(y)  # no. of lines
    m = len(x[0])  # no. of columns
    i = 1
    avgError = 1000000000

    while avgError > maxError:
        print("iteration: ", i)
        i += 1

        computedOutputs = []
        for row in range(n):
            # Compute f(x)
            computedOutput = 0
            for col in range(m):
                computedOutput += x[row][col] * beta[col]

            computedOutputs.append(computedOutput)

        errors = []
        for row in range(n):
            # Error = computedOutput - realOutput
            errors.append(computedOutputs[row] - y[row])

        for col in range(m):
            # Adjust the coefficients
            aux = 0
            for row in range(n):
                aux += x[row][col] * errors[row]

            beta[col] = beta[col] - (learningRate / n) * aux

        avgError = math.sqrt(1 / n * sum([error ** 2 for error in errors]))
        avgErrors.append(avgError)

        coefficients.append(beta)

    return coefficients[-1], avgErrors


def main():
    x, y = readData("db.txt")

    learningRate = 0.0001
    maxError = 0.4
    beta = np.random.rand(6)

    beta, avgErrors = descendingGradient(x, y, beta, learningRate, maxError)

    print(avgErrors[-1])
    print(beta)


main()
