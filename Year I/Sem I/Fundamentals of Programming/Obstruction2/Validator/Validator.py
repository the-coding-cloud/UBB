from Domain.Entity import Square
from Exceptions.GameException import GameException
import unittest

class SquareValidator:
    def __init__(self, row, column):
        self.__row = row
        self.__column = column
        
    def validateSquare(self, square):
        '''
        Verifies if a certain square is or not on the board
        '''
        
        errors = ""
        
        if square.getRow() < 0 or square.getRow() >= self.__row:
            errors += "Invalid row!\n"
            
        if square.getColumn() < 0 or square.getColumn() >= self.__column:
            errors += "Invalid column!\n"
            
        if len(errors) != 0:
            raise GameException(errors)
        
        return True
    
class SizeValidator:
    def __init__(self):
        pass
    
    def validateTableSize(self, row, column):
        '''
        Verifies if the table size is within limits of decency
        ''' 
        errors = ""
        
        try:
            row = int(row)
            column = int(column)
        except:
            GameException("That's not an integer man")
        
        if row <= 0 or row > 15:
            errors += "Invalid row size!\n"
            
        if column <= 0 or column > 15:
            errors += "Invalid column size!\n"
            
        if len(errors) != 0:
            raise GameException(errors)
        
        return True
        
class TestValidator(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testValidateSquare(self):
        squareValidator = SquareValidator(2, 2)
        square = Square(0, 0)
        self.assertTrue(squareValidator.validateSquare(square))
        
        square = Square(0, 3)
        try:
            squareValidator.validateSquare(square)
            self.assertEqual(False)
        except GameException as ge:
            self.assertEqual(str(ge), "Invalid column!\n")
            
    def testValidateTableSize(self):
        sizeValidator = SizeValidator()
        
        self.assertTrue(sizeValidator.validateTableSize(2, 3))
        
        try:
            sizeValidator.validateTableSize(2, -3)
            self.assertEqual(False)
        except GameException as ge:
            self.assertEqual(str(ge), "Invalid column size!\n")
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
    