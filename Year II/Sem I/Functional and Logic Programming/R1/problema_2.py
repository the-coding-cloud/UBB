class Nod:
    def __init__(self, e):
        self.e = e
        self.urm = None
    
class Lista:
    def __init__(self):
        self.prim = None
        
    def createList(self):
        self.prim = self.createList_rec()
    
    def createList_rec(self):    
        x = int(input("x="))
        if x == 0:
            return None
        else:
            nod = Nod(x)
            nod.urm = self.createList_rec()
            return nod
    
    def sublist(self):
        self.prim = self.prim.urm
        
    def firstElement(self):
        return self.prim.e
    
    def isEmpty(self):
        if self.prim == None:
            return True
        else:
            return False
        
    def addFirst(self, e):
        nod = Nod(e);
        nod.urm = self.prim
        self.prim = nod
        
    def substituteElement(self, i, v):
        self.substituteElementRec(self.prim, i, v)
        
    def substituteElementRec(self, nod, i, v):
        if i == 1:
            nod.e = v
        elif nod == None:
            nod = Nod(v)
        else:
            self.substituteElementRec(nod.urm, i, v)
            
            
l=Lista()
l.createList_rec()
l.substituteElement(3, 4)