class discipline:
    def __init__(self, disciplineID, disciplineName):
        self.disciplineID = disciplineID
        self.disciplineName = disciplineName
    
    def __eq__(self, otherDiscipline):
        if self.disciplineID == int(otherDiscipline.getDisciplineID()):
            return True
        return False
    
    def __str__(self):
        return "Discipline ID: "+str(self.getDisciplineID())+"; Discipline name: "+str(self.getDisciplineName())
    
    def getDisciplineID(self):
        return self.disciplineID
    
    def getDisciplineName(self):
        return self.disciplineName
     
    def setDisciplineName(self, newDisciplineName):
        self.disciplineName = newDisciplineName
        