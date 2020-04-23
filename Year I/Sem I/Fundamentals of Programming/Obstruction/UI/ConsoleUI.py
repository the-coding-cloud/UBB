from Service.GameService import *
from Validator.Validator import SizeValidator 

class ConsoleUI:
    def __init__(self, gameService, sizeValidator):
        dimensions = self.UIPickSize()
        self.gameService = gameService
        self.sizeValidator = sizeValidator
        
    def UIPickSize(self):
        numberOfRows = input("Enter the number of rows")
        numberOfColumns = input("Enter the number of columns")
        self.sizeValidator.validTableSize(numberOfRows, numberOfColumns)
        return [numberOfRows, numberOfColumns]
        