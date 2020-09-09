import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Conv2D, Dropout, Flatten, MaxPooling2D


def prepareData():
    # Load the data
    (x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

    # Reshape the array to 4-dims so that it can work with Keras API
    x_train = x_train.reshape(x_train.shape[0], x_train.shape[1], x_train.shape[2], 1)
    x_test = x_test.reshape(x_test.shape[0], x_test.shape[1], x_test.shape[2], 1)

    # Cast values to float so that division surely returns floating point numbers
    x_train = x_train.astype(float)
    x_test = x_test.astype(float)
    inputShape = (x_train.shape[1], x_train.shape[2], 1)  # (28, 28, 1)

    # Normalizing the RGB codes by dividing it to the max RGB value (basically rescale from [0,255] to [0.0, 1.0])
    x_train /= 255
    x_test /= 255
    return (x_train, y_train), (x_test, y_test), inputShape


def createCNN(inputShape):
    # Creating a Sequential Model and adding the layers
    cnn = Sequential()

    # Add Convolutional Layer, with a filter of size 3x3
    cnn.add(Conv2D(28, kernel_size=(3, 3), input_shape=inputShape))

    # Add Pooling Layer, of size 2x2
    cnn.add(MaxPooling2D(pool_size=(2, 2)))

    # Flattens the 2D arrays for fully connected layers
    cnn.add(Flatten())

    # Add a layer with 128 neurons & activation function is ReLU
    cnn.add(Dense(128, activation=tf.nn.relu))

    # Prevents over-fitting by "dropping" neurons with a probability of 20%
    cnn.add(Dropout(0.2))

    # We have 10 labels in the end (0, 1,...,9)
    # Seemed to also work fine (even faster actually) with softmax and softsign (I literally tried them one by one)
    cnn.add(Dense(10, activation=tf.nn.sigmoid))

    cnn.compile(optimizer='adam',
                loss='sparse_categorical_crossentropy',
                metrics=['accuracy'])

    return cnn


def trainAndEvaluateCNN(cnn, inputTrain, outputTrain, inputTest, outputTest):
    cnn.fit(x=inputTrain, y=outputTrain, epochs=5)
    cnn.evaluate(inputTest, outputTest)
    return cnn


def main():
    (inputTrain, outputTrain), (inputTest, outputTest), inputShape = prepareData()
    cnn = createCNN(inputShape)
    trainAndEvaluateCNN(cnn, inputTrain, outputTrain, inputTest, outputTest)

main()