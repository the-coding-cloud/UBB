import unittest
class Square:
    def __init__(self, row, column):
        self.__row = row
        self.__column = column
        
    def __eq__(self, otherSquare):
        if self.__row == otherSquare.getRow() and self.__column == otherSquare.getColumn():
            return True
        
        return False
    
    def getRow(self):
        '''
        Returns the corresponding row of a square under the form of an integer
        '''
        return self.__row
    
    def getColumn(self):
        '''
        Returns the corresponding column of a square under the form of an integer
        '''
        return self.__column
        
        
class testSquare(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testGetRow(self):
        square = Square(1, 2)
        self.assertTrue(square.getRow(), 1)
        
    def testGetColumn(self):
        square = Square(1, 2)
        self.assertTrue(square.getColumn(), 2)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)