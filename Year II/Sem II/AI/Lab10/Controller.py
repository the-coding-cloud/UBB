from Lab10.Model import Temperature, Power, Capacity, FuzzyRules


class Repository:
    def __init__(self):
        self.temperatures = Temperature().getAllTemperatures()
        self.powers = Power().getPowers()
        self.capacities = Capacity().getCapacities()
        self.rules = FuzzyRules().getRules()


def inverseTriangle(y, boundary):
    [a,b,c] = boundary
    return ((y*(b-a)+a) + (y * (b-c) + c)) / 2


class Controller:
    def __init__(self, repo: Repository):
        self.repository = repo

    def applyRules(self, temperature, capacity):
        rules = self.repository.rules
        allTemperatures = self.repository.temperatures
        allCapacity = self.repository.capacities
        allPowers = self.repository.capacities
        fuzzySet = []
        for (temp, cap, power) in rules:
            print("if temp is ", temp, " and capacity is ", cap, " power is ", power )
            for (t, boundary, function) in allTemperatures:
                if t == temp:
                    resultTemperature = function(temperature, boundary)
                    break
            for (c, boundary, function) in allPowers:
                if c == cap:
                    resultCapacity = function(capacity, boundary)
                    break
            print("membership temp =", resultTemperature, "membership cap = ", resultCapacity)
            powerX = min(resultCapacity, resultTemperature)
            if powerX != 0:
                for (p, boundary, function) in allPowers:
                    if power == p:
                        print(powerX, boundary, p)
                        fuzzySet.append((inverseTriangle(powerX,boundary), powerX))
                        print("power = ", inverseTriangle(powerX, boundary), "membership power =", powerX)
            else:
                print("fuzzy set for this rule is null")
            print("-----------------")
        return fuzzySet

    def runAlg(self, temperature, capacity):
        fuzzySet = self.applyRules(temperature, capacity)
        sum1 = 0
        sum2 = 0
        for (x, result) in fuzzySet:
            sum1 = sum1 + x * result
            sum2 = sum2 + result

        if sum2 != 0:
            print(sum1 / sum2)
        else:
            print(0)
