from Lab10.Controller import Controller, Repository


class UI:
    def __init__(self, c: Controller):
        self.controller = c

    def run(self):
        while True:
            temperature = float(input("Temperature(20-120): "))
            capacity = float(input("Capacity(0-10): "))
            self.controller.runAlg(temperature, capacity)


if __name__ == '__main__':
    r = Repository()
    c = Controller(r)
    ui = UI(c)
    ui.run()