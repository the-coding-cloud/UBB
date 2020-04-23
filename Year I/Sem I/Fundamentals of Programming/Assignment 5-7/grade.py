class grade:
    def __init__(self, disciplineID, studentID, gradeValue):
        self.disciplineID = disciplineID
        self.studentID = studentID
        self.gradeValue = gradeValue
        
    def __eq__(self, otherGrade):
        if self.disciplineID == int(otherGrade.getDisciplineID):
            return True
        return False
    
    def __str__(self):
        return "Student ID: "+str(self.getStudentID())+"; Discipline ID: "+str(self.getDisciplineID()) + "; Grade Value: " + str(self.getGradeValue())
    
    def getDisciplineID(self):
        return self.disciplineID
    
    def getStudentID(self):
        return self.studentID
    
    def getGradeValue(self):
        return self.gradeValue

    