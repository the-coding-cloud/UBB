from NeuralNetwork import NeuralNetwork
from Repository import Repository
import matplotlib.pyplot as mpl
import numpy as np

class Controller:
    def __init__(self, repo : Repository):
        self.repo = repo

    def runAlg(self):
        data = self.repo.data
        xL = []
        yL = []
        for elem in data:
            xL.append(elem[:-1])
            yL.append([elem[-1]])
        x = np.array(xL)
        y = np.array(yL)
        nn = NeuralNetwork(x, y, 2)
        nn.loss = []
        iterations = []
        for i in range(1000):
            nn.feedforward()
            nn.backprop(0.00000001)
            iterations.append(i)

        print(min(nn.loss))
        mpl.plot(iterations, nn.loss, label='loss value vs iteration')
        mpl.xlabel('Iterations')
        mpl.ylabel('loss function')
        mpl.legend()
        mpl.show()
