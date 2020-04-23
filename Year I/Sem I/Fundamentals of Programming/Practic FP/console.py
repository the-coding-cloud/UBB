from service import *

class Console:
    def __init__(self, service):
        self.__service = service
        
    def uiSwap(self, w1, l1, w2, l2):
        self.__service.setUndo()
        string = self.__service.swap(w1, l1, w2, l2)
        self.__service.setShuffled(string)
        self.__service.decreaseScore()
        
    def uiUndo(self):
        self.__service.undo()
    
    def run(self):
        
        while True:
            try:
                
                if self.__service.isWon():
                    print(self.__service.getShuffled())
                    print("You won, congrats")
                    print("Your score is: " + str(self.__service.getScore()))
                    return
                
                elif self.__service.getScore() == 0:
                    print("Game over, you lost")
                    return
                
                print("Score is: " + str(self.__service.getScore()))
                print(self.__service.getShuffled())
                
                command = input("Enter valid command, please: ")
                attributes = command.strip().split()
                if len(attributes) == 6:
                    if attributes[0] != "swap":
                        raise ValueError
                    
                    w1 = int(attributes[1])
                    l1 = int(attributes[2])
                    w2 = int(attributes[4])
                    l2 = int(attributes[5])
                    
                    indexes = self.__service.getValidIndexes()
                    
                    if w1 >= len(indexes) or w2 >= len(indexes):
                        raise ValueError
                    
                    if l1 not in indexes[w1]:
                        raise ValueError
                    
                    if l2 not in indexes[w2]:
                        raise ValueError
                    
                    self.uiSwap(w1, l1, w2, l2)
                    
                elif len(attributes) == 1 and attributes[0] == "undo":
                    self.uiUndo()
                    
                else:
                    raise ValueError
          
            except ValueError:
                print("I said a valid command...")