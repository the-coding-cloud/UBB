class Move:
    def __init__(self, x, y, mark):
        self.x = x 
        self.y = y 
        self.mark = mark
    
    def __eq__(self, otherMove):
        if self.x == otherMove.getX() and self.y == otherMove.getY():
            return True
        
        return False
    
    def __str__(self):
        return str(self.x) + " " + str (self.y) + " " + self.mark
    
    def getX(self):
        return self.x
    
    def getY(self):
        return self.y
    
    def getMark(self):
        return self.mark
        
    
    