import numpy as np
import matplotlib.pyplot as mpl


class Repository:
    def __init__(self, filepath):
        self.x = None
        self.y = None
        self.readData(filepath)

    def readData(self, filePath):
        with open(filePath, "r") as file:
            x = []
            y = []
            for line in file:
                if line != "\n":
                    inputs = list(map(float, line.strip(" ").split(" ")))
                    output = inputs.pop()
                    x.append(np.array(inputs))
                    y.append(np.array([output]))

        self.x = np.array(x)
        self.y = np.array(y)


class NeuralNetwork:
    def __init__(self, x, y, hidden, a):
        self.input = x
        self.weights1 = np.random.rand(self.input.shape[1], hidden)
        self.weights2 = np.random.rand(hidden, 1)
        self.y = y
        self.layer1 = None
        self.output = np.zeros(self.y.shape)
        self.loss = []
        self.a = a

    def linearFunction(self, x):
        return self.a * x

    def linearDerivative(self, x):
        return self.a

    # the function that computes the output of the network for some input
    def feedForward(self):
        self.layer1 = self.linearFunction(np.dot(self.input, self.weights1))
        self.output = self.linearFunction(np.dot(self.layer1, self.weights2))

    # the backpropagation algorithm
    def backPropagation(self, l_rate):
        # application of the chain rule to find derivative of the
        # loss function with respect to weights2 and weights1
        d_weights2 = np.dot(self.layer1.T, (2 * (self.y - self.output) * self.linearDerivative(self.output)))

        d_weights1 = np.dot(self.input.T, (np.dot(2 * (self.y - self.output) * self.linearDerivative(self.output),
                                                  self.weights2.T) * self.linearDerivative(self.layer1)))

        # update the weights with the derivative (slope) of the loss function
        self.weights1 += l_rate * d_weights1
        self.weights2 += l_rate * d_weights2
        self.loss.append(sum((self.y - self.output) ** 2) / len(self.input))


class Controller:
    def __init__(self, repo):
        self.repo = repo
        self.ANN = NeuralNetwork(self.repo.x, self.repo.y, 1, 1.3)

    def train(self):
        self.ANN.loss = []
        iterations = []
        for i in range(500):
            self.ANN.feedForward()
            self.ANN.backPropagation(0.0000001)
            iterations.append(i)

        print(min(self.ANN.loss))
        mpl.plot(iterations, self.ANN.loss, label='loss value vs iteration')
        mpl.xlabel('Iterations')
        mpl.ylabel('loss function')
        mpl.legend()
        mpl.show()

    def predict(self, inputVals):
        self.ANN.input = inputVals
        self.ANN.feedForward()
        return self.ANN.output


r = Repository("db.txt")
c = Controller(r)
c.train()
