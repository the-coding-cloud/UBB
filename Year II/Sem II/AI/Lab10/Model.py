def triangleFunction(x, boundary):
    [a, b, c] = boundary
    if x <= a:
        return 0
    if a <= x <= b:
        return (x - a) / (b - a)
    if b <= x <= c:
        return (c - x) / (c - b)
    if x >= c:
        return 0


def trapeziumFunction(x, boundary):
    [a, b, c, d] = boundary
    if x <= a:
        return 0
    if a <= x <= b:
        return (x - a) / (b - a)
    if b <= x <= c:
        return 1
    if c <= x <= d:
        return (d - x) / (d - c)
    if x >= d:
        return 0


class Humidity:
    def __init__(self):
        self.fuzzyRegions = None
        self.setFuzzyRegions()

    def setFuzzyRegions(self):
        self.fuzzyRegions = []
        self.fuzzyRegions.append(("dry", [0, 0, 50], triangleFunction))
        self.fuzzyRegions.append(("normal", [0, 50, 100], triangleFunction))
        self.fuzzyRegions.append(("wet", [50, 100, 100], triangleFunction))

    def getFuzzyRegions(self):
        return self.fuzzyRegions


class Time:
    def __init__(self):
        self.fuzzyRegions = None
        self.setFuzzyRegions()

    def setFuzzyRegions(self):
        self.fuzzyRegions = []
        self.fuzzyRegions.append(("short", [0, 0, 50], triangleFunction))
        self.fuzzyRegions.append(("medium", [0, 50, 100], triangleFunction))
        self.fuzzyRegions.append(("long", [50, 100, 100], triangleFunction))

    def getFuzzyRegions(self):
        return self.fuzzyRegions


class Temperature:
    def __init__(self):
        self.fuzzyRegions = None
        self.setFuzzyRegions()

    def setFuzzyRegions(self):
        self.fuzzyRegions = []
        self.fuzzyRegions.append(("very cold", [-30, -30, -20, 5], trapeziumFunction))
        self.fuzzyRegions.append(("cold", [-5, 0, 10], triangleFunction))
        self.fuzzyRegions.append(("normal", [5, 10, 15, 20], trapeziumFunction))
        self.fuzzyRegions.append(("warm", [15, 20, 25], triangleFunction))
        self.fuzzyRegions.append(("hot", [25, 30, 35, 35], trapeziumFunction))

    def getFuzzyRegions(self):
        return self.fuzzyRegions

class FuzzyRules:
    def __init__(self):
        self.rules = None
        self.setRules()

    def setRules(self):
        self.rules = []
        self.rules.append(("very cold", "wet", "short"))
        self.rules.append(("very cold", "normal", "short"))
        self.rules.append(("very cold", "dry", "medium"))
        self.rules.append(("cold", "wet", "short"))
        self.rules.append(("cold", "normal", "medium"))
        self.rules.append(("cold", "dry", "long"))
        self.rules.append(("normal", "wet", "short"))
        self.rules.append(("normal", "normal", "medium"))
        self.rules.append(("normal", "dry", "long"))
        self.rules.append(("warm", "wet", "short"))
        self.rules.append(("warm", "normal", "medium"))
        self.rules.append(("warm", "dry", "long"))
        self.rules.append(("hot", "wet", "medium"))
        self.rules.append(("hot", "normal", "long"))
        self.rules.append(("hot", "dry", "long"))

    def getRules(self):
        return self.rules

