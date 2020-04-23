from Repo.RepoMoves import *
from Model.Player import *
from random import randint


class GameService:
    def __init__ (self, repo, player1, player2, validator):
        self.repo = repo
        self.player1 = player1
        self.player2 = player2
        self.validator = validator
        
    def addMove(self, move):
        self.repo.addMove(move)
        self.repo.sortMoves()
        
    def drawTable(self):
        self.repo.drawTable()
    
    def computerMove(self):
        while True:
            newMove = Move(randint(self.repo.row), randint(self.repo.column))
            if self.validator.validComputerMove(newMove):
                self.addMove(newMove)
                break
        
    def userMove(self, x, y):
        newMove = Move(x, y)
        self.validator.validMove(newMove)
        if not self.repo.existsMove(newMove):
                self.addMove(newMove)
            