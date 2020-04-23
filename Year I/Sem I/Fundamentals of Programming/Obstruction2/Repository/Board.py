from Domain.Entity import Square
from Exceptions.GameException import GameException
from texttable import Texttable
import unittest
import copy

class Board:
    def __init__(self, maxRow, maxColumn):
        self.__rows = maxRow
        self.__columns = maxColumn
        self.__moves = [ [ 0 for column in range(0, self.__columns) ] for row in range(0, self.__rows) ]
        
        self.__rowIndexList = []
        for row in range(self.__rows):
            self.__rowIndexList.append(row)
        
        self.__columnIndexList = []
        for column in range(self.__columns):
            self.__columnIndexList.append(column)
            
    def getPossibleMoves(self):
        '''
        Returns a list containing the coordinates of the empty squares on the board,
        under the form of Square objects
        
        Input: square - Square object
        Output: possibleMoves - list of Square objects 
        '''
        possibleMoves = []
        for row in range(self.__rows):
            for column in range(self.__columns):
                if self.__moves[row][column] == 0:
                    possibleMoves.append(Square(row, column))
        return possibleMoves
            
    def addNeighbours(self, square):
        '''
        Marks the neighbours of a given square on the board, by placing "+"
        in the corresponding squares
        
        Input: square - Square object
        '''
        row = square.getRow()
        column = square.getColumn()
        
        rowDirections = [-1, -1, 0, 1, 1, 1, 0, -1]
        columnDirections = [0, 1, 1, 1, 0, -1, -1, -1]
        
        for index in range(0, 8):
            newRow = row + rowDirections[index]
            newColumn = column + columnDirections[index]
            if newRow >= 0 and newRow < self.__rows and newColumn >= 0 and newColumn < self.__columns:
                if self.__moves[newRow][newColumn] == 0:
                    self.__moves[newRow][newColumn] = "+"
        
    def addMove(self, square, symbol):
        '''
        If the chosen square is empty, the function marks the given square with the given symbol.
        Else, the function raises a GameException
        
        Input: square - Square object, symbol - "X" or "O"
        '''
        possibleMoves = self.getPossibleMoves()
        successful = False
        
        for move in possibleMoves:
            if move == square:
                self.__moves[square.getRow()][square.getColumn()] = symbol
                successful = True
        
        if not successful:
            raise GameException ("Square already taken.")
    
            
    def __str__(self):
        table = Texttable()
        line = []
        line.append(' ')
        line = line + self.__columnIndexList
        table.add_row(line)
        
        symbols = {'X':'X', 'O':'O', 0:' ', '+':'+'}
        for rowNumber in self.__rowIndexList:
            moves = self.__moves[rowNumber][:]
            for columnNumber in self.__columnIndexList:
                moves[columnNumber] = symbols[moves[columnNumber]]
            line = []
            line.append(rowNumber)
            line = line + moves
            table.add_row(line)

        return table.draw()
    
    def copy(self):
        board = Board(self.__rows, self.__columns)
        board.__moves = copy.deepcopy(self.__moves)
        return board
    
            
class TestBoard(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)

    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testGetPossibleMoves(self):
        board = Board(2, 2)
        self.assertEqual(board.getPossibleMoves(), [Square(0, 0), Square(0, 1), Square(1, 0), Square(1, 1)])
        
    def testAddNeighbours(self):
        board = Board(2, 2)
        board.addNeighbours(Square(0, 0))
        self.assertEqual(board.getPossibleMoves(), [Square(0, 0)])
        
    def testAddMove(self):
        board = Board(2, 2)
        board.addMove(Square(0, 0), "X")
        self.assertEqual(board.getPossibleMoves(), [Square(0, 1), Square(1, 0), Square(1, 1)])