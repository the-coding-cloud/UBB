class student:
    def __init__(self, studentID, studentName):
        self.studentID = studentID
        self.studentName = studentName
    
    def __eq__(self, otherStudent):
        if self.studentID == int(otherStudent.getStudentID()):
            return True
        return False
    
    def __str__(self):
        return "Student ID: "+str(self.getStudentID())+"; Student name: "+str(self.getStudentName())
      
    def getStudentID(self):
        return self.studentID
    
    def getStudentName(self):
        return self.studentName
 
    def setStudentName(self, newStudentName):
        self.studentName = newStudentName