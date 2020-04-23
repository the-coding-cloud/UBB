"""
Task B:
    Design and deploy an application in python that generates random numbers. From a
    menu the user can choose the desired distribution of probability (at least 2 from below), the
    interval. After generating a set of numbers show a graphic to compare it with the desired output.
"""

from numpy import random
from matplotlib import pyplot as plt


def printDistributionOptions():
    commands = ""
    commands += "Pick a distribution:\n"
    commands += "1. Uniform;\n"
    commands += "2. Normal;\n"
    commands += "Type 0 to exit.\n"
    print(commands)


def generateNumbersUniform(a, b, size):
    randomNumbers = random.uniform(a, b, size)
    plt.hist(randomNumbers)
    plt.xlabel('meh')
    plt.show()


def generateNumbersNormal(a, b, size):
    mean = (float(a + b)) / 2
    std = 1
    randomNumbers = random.normal(mean, std, size=size)
    plt.hist(randomNumbers)
    plt.xlabel('meh')
    plt.show()


def run():
    printDistributionOptions()
    distributions = {
        1: generateNumbersUniform,
        2: generateNumbersNormal
    }

    distribution = int(input())
    a = int(input("a: "))
    b = int(input("b: "))
    size = int(input("Sample size: "))

    distributions[distribution](a, b, size)


run()
