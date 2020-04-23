from Repository.Board import Board
from Validator.Validator import SquareValidator
from Domain.Entity import Square

from random import randint
import unittest


class Game:
    def __init__(self, maxRows, maxColumns):
        self.__board = Board(maxRows, maxColumns)
        self.__validator = SquareValidator(maxRows, maxColumns)
        
    def playerTurn(self, square, symbol):
        '''
        Adds the player move on the board
        Input: square - Square object, symbol - "X" or "O"
        '''
        self.__validator.validateSquare(square)
        self.__board.addMove(square, symbol)
        self.__board.addNeighbours(square)
        
    def computerTurn(self, symbol):
        '''
        Adds the computer move on the board
        Input: symbol - "X" or "O"
        '''
        possibleMoves = self.__board.getPossibleMoves()
        
        moved = False
        
        for move in possibleMoves:
            board = self.__board.copy()
            board.addMove(move, symbol)
            board.addNeighbours(move)
            if board.getPossibleMoves() == []:
                self.__board.addMove(move, symbol)
                moved = True
                
        if not moved:        
            square = possibleMoves[randint(0, len(possibleMoves)-1)]
            self.__board.addMove(square, symbol)
            self.__board.addNeighbours(square)
        
      
    def isWon(self):
        if self.__board.getPossibleMoves() == []:
            return True
        return False
    
    @property
    def board(self):
        return self.__board
    

class TestGameService(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testIsWon(self):
        game = Game(2, 2)
        game.playerTurn(Square(0, 0), "X")
        self.assertTrue(game.isWon())
        
        game = Game(2, 2)
        game.computerTurn("O")
        self.assertTrue(game.isWon())
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)