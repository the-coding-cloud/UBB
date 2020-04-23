
class UndoControl:
    def __init__(self):
        self.history = []
        self.index = -1
        
    def recordOperation(self, operation):
        self.history.append(operation)
        self.index += 1
        
        print(self.history)
        print(self.index)
        
    def undo(self):
        if self.index == -1:
            return False
        
        operation = self.history[self.index]
        if operation.functionUndo.cascadeOp == True:
            operation.undo()
            self.index -= 1
            
            operation = self.history[self.index]
            operation.undo()
            self.index -= 1
        
        else:
            operation.undo()
            self.index -= 1
            
        return True
    
    def redo(self):
        if self.index == len (self.history)-1:
            return False
        self.index += 1
        
        operation = self.history[self.index]
        if operation.functionRedo.cascadeOp == True:
            operation.redo()
            
            self.index += 1
            operation = self.history[self.index]
            operation.redo()
        
        else:
            operation.redo()
        
        return True
    
    def updateHistory(self):
        if len(self.history)>0:
            i = self.index
            while i < len(self.history)-1:
                self.history.pop(i)
                
        print(self.index)
                
class FunctionCall:
    def __init__(self, functionRef, cascadeOp, *parameters):
        self.functionRef = functionRef
        self.cascadeOp = cascadeOp
        self.parameters = parameters
        print(self.parameters)
        
    def call(self):
        self.functionRef(*self.parameters)
        
class Operation:
    def __init__(self, functionUndo, functionRedo):
        self.functionRedo = functionRedo
        self.functionUndo = functionUndo
        
    def undo(self):
        self.functionUndo.call()
        
    def redo(self):
        self.functionRedo.call()
