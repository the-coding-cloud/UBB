import random

header = ["left weight", "left value", "right weight", "right value", "class"]


def uniqueValues(rows, col):
    # Find the unique values for a column in a data set
    return list(set([row[col] for row in rows]))


def classCounts(rows):
    """
    Counts the how many rows belong to each class in a dataset.
    """
    counts = {}

    for row in rows:
        # in our data set format, the label is always the last column
        label = row[-1]
        if label not in counts:
            counts[label] = 1
        else:
            counts[label] += 1

    return counts


def isNumeric(value):
    """Test if a value is numeric."""
    return isinstance(value, int) or isinstance(value, float)


class Question:
    def __init__(self, column, values):
        self.column = column
        self.values = values

    def match(self, example):
        # Compare the feature value in an example to the
        # feature value in this question.
        val = example[self.column]

        return val

    def getValues(self):
        return self.values[:]

    def __repr__(self):
        return "What %s is it?" % (header[self.column])


def gini(rows):
    """
    Calculate the Gini Impurity for a list of rows.
    """
    counts = classCounts(rows)
    impurity = 1

    for label in counts:
        labelProbability = counts[label] / float(len(rows))
        impurity -= labelProbability ** 2

    return impurity


def infoGain(childNodes, current_uncertainty):
    """
    Information Gain
    """
    totalSize = 0

    for node in childNodes.values():
        totalSize += len(node)

    for node in childNodes.values():
        current_uncertainty -= (float(len(node)) / totalSize) * gini(node)

    return current_uncertainty


def partition(rows, question):
    """
    Partitions a dataset.
    """

    childNodes = {}

    for value in range(1, 6):
        childNodes[str(value)] = []

    for row in rows:
        value = question.match(row)
        childNodes[value].append(row)

    return childNodes


def findBestSplit(rows, alreadyTakenAttributes):
    """
    Find the best question to ask by iterating over every feature / value
    and calculating the information gain.
    """
    best_gain = 0  # keep track of the best information gain
    best_question = None  # keep track of the attribute that produced it
    current_uncertainty = gini(rows)
    nrAttributes = len(rows[0]) - 1  # number of columns

    for col in range(nrAttributes):  # for each feature
        if len(alreadyTakenAttributes) == 0 or col not in alreadyTakenAttributes:
            values = uniqueValues(rows, col)  # unique values in the column

            question = Question(col, values)

            childRows = partition(rows, question)

            # Skip this split if it doesn't divide the data set.
            nrChildNodes = 0
            for child in childRows.values():
                if len(child) > 0:
                    nrChildNodes += 1

            if nrChildNodes == 1:
                continue

            # Calculate the information gain from this split
            gain = infoGain(childRows, current_uncertainty)

            if gain >= best_gain:
                best_gain, best_question = gain, question

    if best_question is not None:
        alreadyTakenAttributes.append(best_question.column)

    return best_gain, best_question, alreadyTakenAttributes


class Leaf:
    """
    Classifies the data
    """
    def __init__(self, rows):
        self.predictions = classCounts(rows)


class InternalNode:
    """
    Holds a reference to the question + a list of the child nodes.
    """

    def __init__(self, question, branches):
        self.question = question
        self.branches = branches


def buildTree(rows, alreadyTakenAttributes):
    """
    Build the tree
    """

    # Try partitioning the data set on each of the unique attribute,
    # calculate the information gain and return the question that produces the highest gain.
    gain, question, takenAttributes = findBestSplit(rows, alreadyTakenAttributes)

    # Base case: no further info gain; return leaf
    if gain == 0:
        return Leaf(rows)

    childRows = partition(rows, question)

    branches = {}

    for key in childRows.keys():
        if len(childRows[key]) > 0:
            branches[key] = buildTree(childRows[key], takenAttributes)
        else:
            branches[key] = Leaf([["L"], ["B"], ["R"]])

    return InternalNode(question, branches)


def classify(row, node):
    # Base case: we've reached a leaf
    if isinstance(node, Leaf):
        return node.predictions

    else:
        value = node.question.match(row)
        return classify(row, node.branches[value])


def printLeaf(counts):
    total = sum(counts.values()) * 1.0
    probabilities = {}
    for label in counts.keys():
        probabilities[label] = str(int(counts[label] / total * 100)) + "%"
    return probabilities


def trainTree(trainingData):
    return buildTree(trainingData, [])


def readData(filepath):
    totalData = []
    file = open(filepath)
    for line in file:
        data = line.strip().split(',')
        label = data.pop(0)
        data.append(label)
        totalData.append(data)

    return totalData


def shuffleData(totalData):
    random.shuffle(totalData)
    trainingData = totalData[:500]
    testingData = totalData[500:]

    return trainingData, testingData


def evaluateTree(tree, testingData):
    total = len(testingData)
    guessed = 0
    for row in testingData:
        leaf = classify(row, tree)
        chance = 0
        bestPrediction = None

        for prediction in leaf.keys():
            if leaf[prediction] > chance:
                chance = leaf[prediction]
                bestPrediction = prediction

        if bestPrediction == row[-1]:
            guessed += 1

        # print("Actual: %s. Predicted: %s" % (row[-1], print_leaf(leaf)))

    print("Guessed: %s, total: %s" % (guessed, total))

    return float(guessed) * 100 / total


def run():
    totalData = readData("data/balance-scale.data")

    maxAccuracy = 0
    bestTree = None

    for i in range(1000):
        trainingData, testingData = shuffleData(totalData)
        tree = buildTree(trainingData, [])
        accuracy = evaluateTree(tree, testingData)
        if maxAccuracy < accuracy:
            maxAccuracy = accuracy
            bestTree = tree

    print("Max accuracy: %s" % maxAccuracy)
    return bestTree


run()
