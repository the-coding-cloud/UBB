from Model.Move import Move
import unittest


class RepoMoves:
    def __init__(self, row, column):
        self.row = row 
        self.column = column 
        self.moves = []
        
    def __len__(self):
        return len(self.moves)
        
    def addMove(self, move):
        if self.existsMove(move) == False:
            self.moves.append(move)
            self.addNeighbours(move)
        else:
            raise ValueError("Invalid Move")
        
    def existsMove(self, newMove):
        for move in self.moves:
            if newMove == move:
                return True
            
        return False
        
    def addNeighbours(self, move):
        currentX = move.getX()
        currentY = move.getY()
        
        dl = [-1, -1, 0, 1, 1, 1, 0, -1]
        dc = [0, 1, 1, 1, 0, -1, -1, -1]
        
        for i in range(0, 8):
            newX = currentX + dl[i]
            newY = currentY + dc[i]
            if newX >= 0 and newX < self.row and newY >= 0 and newY < self.column:
                neighbour = Move(newX, newY, "#")
                if self.existsMove(neighbour) == False:
                    self.moves.append(neighbour)
                    

    
    def sortMoves(self):
        self.moves.sort(key = lambda x: (x.getX(), x.getY()))
        
    def printMoves(self):
        for move in self.moves:
            print (str(move))
        
    def drawTable (self):
        for i in range(0, self.row):
            row = ""
            for j in range(0, self.column):
                
                emptyMove = Move (i, j, "-")
                found = False
                for move in self.moves:
                    if emptyMove == move:
                        row += move.getMark()
                        found = True
                
                if found == False:
                    row += "-"
                    
            print (row)
            
                    
                
                        


class TestRepoMoves(unittest.TestCase):

    def setUp(self):
        unittest.TestCase.setUp(self)

    def tearDown(self):
        unittest.TestCase.tearDown(self)

    def testExistsMove(self):
        repoMoves = RepoMoves(4, 4)
        move = Move (2, 3, "x")
        otherMove = Move (1, 1, "o")
        
        repoMoves.moves.append(move)
        
        assert repoMoves.existsMove(move) == True
        assert repoMoves.existsMove(otherMove) == False
        
    def testAddNeighbours(self):
        repoMoves = RepoMoves(4, 4)
        move = Move (0, 0, "x")
        
        repoMoves.moves.append(move)
        repoMoves.addNeighbours(move)
        
        assert repoMoves.moves == [move, Move(0, 1, "#"), Move(1, 1, "#"), Move (1, 0, "#")]
        assert len(repoMoves.moves) == 4
        
    def testAddMove(self):
        repoMoves = RepoMoves(5, 4)
        move = Move (0, 0, "x")
        
        repoMoves.addMove(move)
        
        assert len(repoMoves.moves) == 4
        
        try:
            repoMoves.addMove(move)
            assert False
        except:
            assert True
            
        repoMoves.drawTable()
        
        
