import numpy as np

class NeuralNetwork:
    def linearFunction(self, x):
        return x

    def linearDerivative(self, x):
        return 1


    def __init__(self, x, y, hidden):
        self.input = x
        self.weights1 = np.random.rand(self.input.shape[1], hidden)
        self.weights2 = np.random.rand(hidden, 1)
        self.y = y
        self.output = np.zeros(self.y.shape)
        self.loss = []

    # the function that computs the output of the network for some input
    def feedforward(self):
        self.layer1 = self.linearFunction(np.dot(self.input, self.weights1))
        self.output = self.linearFunction(np.dot(self.layer1, self.weights2))

    # the backpropagation algorithm 
    def backprop(self, l_rate):
        # application of the chain rule to find derivative of the    
        # loss function with respect to weights2 and weights1
        d_weights2 = np.dot(self.layer1.T, (2 * (self.y - self.output) *
                                            self.linearDerivative(self.output)))

        d_weights1 = np.dot(self.input.T,  (np.dot(2*(self.y - self.output) *
                                                   self.linearDerivative(self.output), self.weights2.T) * self.linearDerivative(self.layer1)))
# update the weights with the derivative (slope) of the loss function

        self.weights1 += l_rate * d_weights1
        self.weights2 += l_rate * d_weights2
        self.loss.append(sum((self.y - self.output) ** 2)/497)
