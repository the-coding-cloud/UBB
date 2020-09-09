from Controller import Controller
from Repository import Repository

if __name__ == '__main__':
    r = Repository()
    c = Controller(r)
    c.runAlg()