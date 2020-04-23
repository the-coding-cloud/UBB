from Exceptions.GameException import GameException
from Service.GameService import Game
from Domain.Entity import Square
from Validator.Validator import SizeValidator

class ConsoleUI:
    def __init__(self):
        self.__validator = SizeValidator()
        self.__sizes = self.readSize()
        self.__game = Game(self.__sizes[0], self.__sizes[1])
        
    def readSize(self):
        while True:
            try:
                row = int(input("Enter number of rows: "))
                column = int(input("Enter number of columns: "))
                self.__validator.validateTableSize(row, column)
                break
            except:
                ValueError("Invalid input")
        return [row, column]
                
    def readMove(self):
        while True:
            move = input("Enter the coordinates of your next move (row, column): ")
            coordinates = move.strip().split(' ')
            try:
                if len(coordinates) == 2:
                    row = int(coordinates[0])
                    column = int(coordinates[1])
                    break
                else:
                    raise ValueError
            except ValueError:
                print("Invalid move!")
        return Square(row, column)
    
    def run(self):
        turnCheck = 1
        while self.__game.isWon() == False:
            try:
                if turnCheck%2==1:
                    #Human player first
                    print(self.__game.board)
                    move = self.readMove()
                    self.__game.playerTurn(move, "X")
                else:
                    #Computer player second
                    self.__game.computerTurn("O")
            except GameException as ge:
                print(ge)
                turnCheck -= 1
                #If the user fucks up here, we make sure that the loop goes to the user again
                
            turnCheck+=1

        print(self.__game.board)
        #print(self.__game.board.isWon())
        #print(turnCheck)
        if turnCheck%2==1:
            print("Computer wins!")
            print("Player has lost!")
        else:
            print("Player won!")
            print("Computer has lost!")