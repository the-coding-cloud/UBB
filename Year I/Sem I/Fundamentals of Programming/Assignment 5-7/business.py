from studentRepo import *
from disciplineRepo import *
from gradeRepo import *
from undoController import *
from grade import *
import unittest

class business:
    def __init__(self, repo, undoRedoController):
        self.repo = repo
        self.undoRedoController = undoRedoController
                
    def addNewStudent(self, studentID, studentName, recordForUndo=True):
        '''
        Function that adds a new student to the student repository
        Input: studentID - positive int, studentName - string
        '''
        newStudent = student(studentID, studentName)
        self.repo.addStudent(newStudent)
        
        if recordForUndo == True:
            undo = FunctionCall(self.removeStudent, False, studentID, False)
            redo = FunctionCall(self.addNewStudent, False, studentID, studentName, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
        
    def addNewDiscipline(self, disciplineID, disciplineName, recordForUndo=True):
        '''
        Function that adds a new discipline to the discipline repository
        Input: disciplineID - positive int, disciplineName - string
        '''
        newDiscipline = discipline(disciplineID, disciplineName)
        self.repo.addDiscipline(newDiscipline)
        
        if recordForUndo == True:
            undo = FunctionCall(self.removeDiscipline, False, disciplineID, False)
            redo = FunctionCall(self.addNewDiscipline, False, disciplineID, disciplineName, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
        
    def addNewGrade(self, disciplineID, studentID, gradeValue, recordForUndo=True):
        '''
        Function that adds a new grade to the grade repository
        Input: disciplineID, studentID - positive int, gradeValue - float value between 1 and 10
        '''
        newGrade = grade (disciplineID, studentID, gradeValue)
        if gradeValue < 1 or gradeValue > 10:
            raise ValueError ("Invalid grade value")
        self.repo.addGrade(newGrade)
        
        if recordForUndo == True:
            undo = FunctionCall(self.removeGrade, False, disciplineID, studentID, gradeValue)
            redo = FunctionCall(self.addNewGrade, False, disciplineID, studentID, gradeValue, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
            
    def addBackGrades(self, gradesToAdd):
        for grade in gradesToAdd:
            self.addNewGrade(grade[0], grade[1], grade[2], False)

        
    def updateStudent(self, studentID, studentName, recordForUndo=True):
        '''
        Function that updates student name based on studentID
        Input: studentID - positive int, studentName - string
        '''
        previousStudentName = self.repo.findStudentNameByID(studentID)
        self.repo.updateStudentList(studentID, studentName)
        
        if recordForUndo == True:
            undo = FunctionCall(self.updateStudent, False, studentID, previousStudentName, False)
            redo = FunctionCall(self.updateStudent, False, studentID, studentName, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
        

    def updateDiscipline(self, disciplineID, disciplineName, recordForUndo=True):
        '''
        Function that updates discipline name based on disciplineID
        Input: disciplineID - positive int, disicplineName - string
        '''
        previousDisciplineName = self.repo.findDisciplineNameByID(disciplineID)
        self.repo.updateDisciplineList(disciplineID, disciplineName)
        
        if recordForUndo == True:
            undo = FunctionCall(self.updateDiscipline, False, disciplineID, previousDisciplineName, False)
            redo = FunctionCall(self.updateDiscipline, False, disciplineID, disciplineName, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
        
    def printAllStudents(self):
        '''
        Function that prints all students
        '''
        self.repo.printStudents()
        
    def printAllDisciplines(self):
        '''
        Function that prints all disciplines
        '''
        self.repo.printDisciplines()
        
    def removeStudent(self, studentID, recordForUndo=True):
        '''
        Function that removes student based on student ID
        Input: studentID - positive int
        '''
        studentName = self.repo.findStudentNameByID(studentID)
        self.repo.removeStudent(studentID)
        if recordForUndo == True:
            undo = FunctionCall(self.addNewStudent, False, studentID, studentName, False)
            redo = FunctionCall(self.removeStudent, True, studentID, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
           
    def removeDiscipline(self, disciplineID, recordForUndo=True):
        '''
        Function that removes discipline based on discipline ID
        Input: disciplineID - positive int
        '''
        disciplineName = self.repo.findDisciplineNameByID(disciplineID)
        self.repo.removeDiscipline(disciplineID)
        if recordForUndo == True:
            undo = FunctionCall(self.addNewDiscipline, False, disciplineID, disciplineName, False)
            redo = FunctionCall(self.removeDiscipline, True, disciplineID, False)
            operation = Operation(undo, redo)
            self.undoRedoController.recordOperation(operation)
            self.undoRedoController.updateHistory()
        
    def removeGrade (self, disciplineID, studentID, gradeValue):
        '''
        Function that removes only one grade
        '''
        
        index = 0
        while index < len(self.repo.list):
            if self.repo.list[index].getStudentID() == studentID and self.repo.list[index].getDisciplineID() == disciplineID and self.repo.list[index].getGradeValue() == gradeValue:
                del self.repo.list[index]
                break
            index += 1
            
    def removeGradesByStudentID(self, studentID):
        studentGrades = self.repo.removeGradesByStudentID(studentID)
        
        undo = FunctionCall(self.addBackGrades, True, studentGrades)
        redo = FunctionCall(self.removeGradesByStudentID, False, studentID)
        operation = Operation(undo, redo)
        self.undoRedoController.recordOperation(operation)
        self.undoRedoController.updateHistory()
        
    def removeGradesByDisciplineID(self, disciplineID):
        disciplineGrades = self.repo.removeGradesByDisciplineID(disciplineID)
        
        undo = FunctionCall(self.addBackGrades, True,disciplineGrades)
        redo = FunctionCall(self.removeGradesByDisciplineID, False, disciplineID)
        operation = Operation(undo, redo)
        self.undoRedoController.recordOperation(operation)
        self.undoRedoController.updateHistory()
    
    def searchStudent(self, inputString):
        '''
        Function that finds all the matching students based on an input string
        Input: inputString - string
        Output: searchResults - list of all matching students' IDs
        '''
        inputString.lower()
        searchResults = [] 
        for student in self.repo.list:
            studentID = str(student.getStudentID())
            studentName = str(student.getStudentName())
            studentName = studentName.lower()
            if studentID.find(inputString) != -1 or studentName.find(inputString) != -1:
                searchResults.append(studentID)
        return searchResults
    
        
    def searchDiscipline(self, inputString):
        '''
        Function that finds all the matching disciplines based on an input string
        Input: inputString - string
        Output: searchResults - list of all matching disciplines' IDs
        '''
        inputString = inputString.lower()
        searchResults = [] 
        for discipline in self.repo.list:
            disciplineID = str(discipline.getDisciplineID())
            disciplineName = str(discipline.getDisciplineName())
            disciplineName = disciplineName.lower()
            if disciplineID.find(inputString) != -1 or disciplineName.find(inputString) != -1:
                searchResults.append(disciplineID)
        return searchResults

    def printStudentByID(self, studentID):
        '''
        Function that prints the data about a student based on its ID
        Input: studentID - positive int
        '''
        index = self.repo.findStudentByID(studentID)
        if index != -1:
            print(str(self.repo.list[index]))
        else:
            raise ValueError("Inexistent student")
        
    def printDisciplineByID(self, disciplineID):
        '''
        Function that prints the data about a discipline based on its ID
        Input: disciplineID - positive int
        '''
        index = self.repo.findDisciplineByID(disciplineID)
        if index != -1:
            print(str(self.repo.list[index]))
        else:
            raise ValueError("Inexistent discipline")
        
    def findStudentsAtDiscipline(self, disciplineID):
        '''
        Function that returns the list of the IDs of students who are enrolled at a given discipline
        Input: disciplineID - positive int
        Output: listOfStudentsID - list of integers
        '''
        listOfStudentsID = []
        for grade in self.repo.list:
            studentID = grade.getStudentID()
            if grade.getDisciplineID() == disciplineID and studentID not in listOfStudentsID:
                listOfStudentsID.append(studentID)
        return listOfStudentsID
    
    def sortStudentsAlphabetically(self, listOfStudentsID):
        '''
        Function that returns a sorted list of students alphabetically based on their IDs
        Input: listOfStudentsID - list of positive integers
        Output: listOfStudents - list of positive integers
        '''
        listOfStudents = []
        for studentID in listOfStudentsID:
            index = self.repo.findStudentByID(studentID)
            studentName = self.repo.list[index].getStudentName()
            listOfStudents.append([studentID, studentName])
            
        listOfStudents.sort(key = lambda a:a[1])
        return listOfStudents
            
    def sortStudentsByAverage(self, listOfStudentsID, disciplineID):
        '''
        Function that returns a sorted list of students in descending order of their average, based on their IDs
        Input: listOfStudentsID - list of positive integers, disciplineID - positive integer
        Output: listOfStudents - list of positive integers
        '''
        listOfStudents = []
        for studentID in listOfStudentsID:
            averageGrade = self.repo.getStudentAverageForDiscipline(studentID, disciplineID)
            listOfStudents.append([studentID, averageGrade])
            
        listOfStudents.sort(key = lambda a:a[1], reverse = True)
        return listOfStudents
    
    def findFailingStudents(self, studentIDList, disciplineIDList):
        '''
        Function that returns a list of IDs of students who are failing at at least one discipline
        Input: studentIDList, disciplineIDList - list of positive integers
        Output: failingStudentsID - list of positive integers
        '''
        failingStudents = []
        for studentID in studentIDList:
            for disciplineID in disciplineIDList:
                averageGrade = self.repo.getStudentAverageForDiscipline(studentID, disciplineID)
                if averageGrade < 5 and averageGrade != 0:
                    failingStudents.append([studentID, averageGrade])
                    break
                
        return failingStudents
    
    def findBestStudents(self, studentIDList, disciplineIDList):
        '''
        Function that returns a sorted list of IDs of students, in descending order of their aggregated average grade
        Input: studentIDList, disciplineIDList - list of positive integers
        Output: bestStudents - list of [studentID, aggregatedAverage] lists, 
                where studentID is a positive int and aggregatedAverage is a float between 1 and 10
        '''
        bestStudents = []
        for studentID in studentIDList:
            aggregatedAverage = 0
            count = 0
            for disciplineID in disciplineIDList:
                averageGrade = self.repo.getStudentAverageForDiscipline(studentID, disciplineID)
                if averageGrade > 0:
                    aggregatedAverage += averageGrade
                    count += 1
                    
            if count > 0:
                aggregatedAverage = aggregatedAverage/count
                bestStudents.append([studentID, aggregatedAverage])
        
        bestStudents.sort(key = lambda a:a[1], reverse = True)     
        return bestStudents
    
    def findBestDisciplines(self, studentIDList, disciplineIDList):
        '''
        Function that returns a sorted list of all disciplines' ID, at which there is at least one grade, 
        sorted in descending order of the average grade received by all students enrolled at that discipline.
        Input: studentIDList, disciplineIDList - list of positive integers
        Output: list of [disciplineID, averageGrade] lists, 
                where disciplineID is a positive int and averageGrade is a float between 1 and 10
        '''
        bestDisciplines = []
        for disciplineID in disciplineIDList:
            aggregatedAverage = 0
            count = 0
            for studentID in studentIDList:
                averageGrade = self.repo.getStudentAverageForDiscipline(studentID, disciplineID)
                if averageGrade > 0:
                    aggregatedAverage += averageGrade
                    count += 1
                    
            if count > 0:
                aggregatedAverage = aggregatedAverage/count
                bestDisciplines.append([disciplineID, aggregatedAverage])
        
        bestDisciplines.sort(key = lambda a:a[1], reverse = True)     
        return bestDisciplines
    
class TestBussiness(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testSearchStudent(self):
        studentRepository = studentRepo()
        studentList = business(studentRepository)
        studentList.addNewStudent(1, "Oana")
        studentList.addNewStudent(2, "Alina")
        assert studentList.searchStudent("na") == ["1", "2"]
        
    def testSearchDiscipline(self):
        disciplineRepository = disciplineRepo()
        disciplineList = business(disciplineRepository)
        disciplineList.addNewDiscipline(1, "Mate")
        disciplineList.addNewDiscipline(2, "Logica")
        assert disciplineList.searchDiscipline("Gi") == ["2"]
        
    def testFindStudentsAtDiscipline(self):
        gradeRepository = gradeRepo()
        gradeList = business(gradeRepository)
        gradeList.addNewGrade(1, 2, 10)
        gradeList.addNewGrade(1, 3, 10)
        gradeList.addNewGrade(1, 4, 10)
        gradeList.addNewGrade(2, 1, 10)
        gradeList.addNewGrade(3, 1, 10)
        assert gradeList.findStudentsAtDiscipline(1) == [2, 3, 4]
        
    def testSortStudentsAlphabetically(self):
        studentRepository = studentRepo()
        studentList = business(studentRepository)
        studentList.addNewStudent(1, "B")
        studentList.addNewStudent(2, "A")
        assert studentList.sortStudentsAlphabetically([1, 2]) == [[2, "A"], [1, "B"]]
        
    def testSortStudentsByAverage(self):
        gradeRepository = gradeRepo()
        gradeList = business(gradeRepository)
        gradeList.addNewGrade(1, 2, 10)
        gradeList.addNewGrade(1, 3, 9)
        gradeList.addNewGrade(1, 4, 9)
        gradeList.addNewGrade(1, 4, 10)
        gradeList.addNewGrade(2, 1, 10)
        gradeList.addNewGrade(3, 1, 10)
        assert gradeList.sortStudentsByAverage([2, 3, 4], 1) == [[2, 10], [4, 9.5], [3, 9]]