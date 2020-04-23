from grade import *
import unittest
class gradeRepo:
    def __init__(self):
        self.list = []
        
    def __len__(self):
        return len(self.list)
    
    def addGrade(self, grade):
        '''
        Function that adds a new grade to the list
        '''
        self.list.append(grade)
        
    def removeGradesByStudentID(self, studentID):
        '''
        Function that removes the grades of a student, based on its ID
        '''
        index = 0
        studentGrades = []
        while index < len(self):
            if studentID == self.list[index].getStudentID():
                studentID = self.list[index].getStudentID()
                disciplineID = self.list[index].getDisciplineID()
                gradeValue = self.list[index].getGradeValue()
                studentGrades.append([disciplineID, studentID, gradeValue])
                del self.list[index]
                index -= 1
            index += 1
        return studentGrades
    
    def removeGradesByDisciplineID(self, disciplineID):
        '''
        Function that removes the grades of a discipline, based on its ID
        '''
        index = 0
        disciplineGrades = []
        while index < len(self):
            if disciplineID == self.list[index].getDisciplineID():
                studentID = self.list[index].getStudentID()
                disciplineID = self.list[index].getDisciplineID()
                gradeValue = self.list[index].getGradeValue()
                disciplineGrades.append([disciplineID, studentID, gradeValue])
                del self.list[index]
                index -= 1
            index += 1
        return disciplineGrades
    
    def getGradeList(self):
        '''
        Function that returns a copy of the grade list
        '''
        return self.list[:]
    
    def printGrades(self):
        '''
        Function that prints all grade data
        '''
        for index in range(0, len(self.list)):
            print(str(self.list[index]))
    
    def getStudentAverageForDiscipline (self, studentID, disciplineID):
        '''
        Function that returns the average grade of a student at a certain discipline, based on their IDs
        '''
        gradeList = [ ]
        for grade in self.list:
            if grade.getStudentID() == studentID and grade.getDisciplineID() == disciplineID:
                gradeList.append(grade.getGradeValue())

        averageGrade = 0
        numberOfGrades = 0
        
        for grade in gradeList:
            averageGrade += grade
            numberOfGrades += 1
            
        if numberOfGrades > 0:
            averageGrade = averageGrade/numberOfGrades
            return averageGrade
        else:
            return 0
         
class TestGradeRepo(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testAddGrade(self):
        gradeToAdd = grade(1, 1, 10)
        gradeList = gradeRepo()
        gradeList.addGrade(gradeToAdd)
        assert gradeList.list == [gradeToAdd]
        
    def testRemoveGradesByStudentID(self):
        gradeList = gradeRepo()
        gradeToAdd = grade(1, 1, 10)
        gradeList.addGrade(gradeToAdd)
        gradeToAdd2 = grade(1, 2, 9)
        gradeList.addGrade(gradeToAdd2)
        gradeList.removeGradesByStudentID(1)
        assert gradeList.list == [gradeToAdd2]
        
    def testRemoveGradesByDisciplineID(self):
        gradeList = gradeRepo()
        gradeToAdd = grade(1, 1, 10)
        gradeList.addGrade(gradeToAdd)
        gradeToAdd2 = grade(2, 2, 9)
        gradeList.addGrade(gradeToAdd2)
        gradeList.removeGradesByDisciplineID(1)
        assert gradeList.list == [gradeToAdd2]
    
    def testGetStudentAverageForDiscipline(self):
        gradeList = gradeRepo()
        gradeToAdd = grade(1, 1, 10)
        gradeList.addGrade(gradeToAdd)
        gradeToAdd2 = grade(1, 1, 9)
        gradeList.addGrade(gradeToAdd2)
        assert gradeList.getStudentAverageForDiscipline(1, 1) == 9.5