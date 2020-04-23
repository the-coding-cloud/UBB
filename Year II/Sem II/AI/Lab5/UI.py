from Lab5.Controller import Controller
from Lab5.Problem import Problem
from Lab5.Ant import Ant

class UI:
    def __init__(self, controller):
        self.controller = controller

    def run(self):
        sol = self.controller.algorithm()
        print("Solution:")
        print(sol.getValues())
        print("Fitness is: ", sol.evaluate())


def main():
    problem = Problem("inputProblem.txt")
    controller = Controller(problem)
    controller.loadParameters("inputParam.txt")
    ui = UI(controller)

    ui.run()


main()
