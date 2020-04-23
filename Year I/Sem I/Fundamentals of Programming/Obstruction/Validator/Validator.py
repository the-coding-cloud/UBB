from Model.Move.Move import getX, getY

class MoveValidator:
    def __init__(self, row, column):
        self.row = row
        self.column = column
        
    def validMove(self, move):
        errors = ""
        
        if move.getX() < 0 or move.getX() >= self.row:
            errors += "Invalid row!\n"
            
        if move.getY() < 0 or move.getY() >= self.column:
            errors += "Invalid column!\n"
            
        if len(errors) != 0:
            raise ValueError(errors)
        
    def validComputerMove(self, move):
        errors = ""
        
        if move.getX() < 0 or move.getX() >= self.row:
            errors += "Invalid row!\n"
            
        if move.getY() < 0 or move.getY() >= self.column:
            errors += "Invalid column!\n"
            
        if len(errors) != 0:
            return False
        
        return True
    
class SizeValidator:
    def __init__(self):
        pass
    
    def validTableSize(self, row, column):
        errors = ""
        
        try:
            row = int(row)
            column = int(column)
        except:
            ValueError("That's not an integer man")
        
        if row <= 0 or row > 15:
            errors += "Invalid row size!\n"
            
        if column <= 0 or column > 15:
            errors += "Invalid column size!\n"
            
        if len(errors) != 0:
            raise ValueError(errors)
        