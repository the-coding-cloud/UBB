from student import *
from audioop import reverse
import unittest

class studentRepo:
    def __init__(self):
        self.list = []
        
    def __len__(self):
        return len(self.list)
    
    def addStudent(self, student):
        '''
        Function that adds a new student to the list
        '''
        if student in self.list:
            raise ValueError("Existing student!")
        self.list.append(student)
            
    def removeStudent(self, studentID):
        '''
        Function that removes a student from the list, based on its ID
        '''
        removed = 0
        index = 0
        while index < len(self.list):
            if studentID == self.list[index].getStudentID():
                del self.list[index]
                removed = 1
                index -=1
            index += 1
            
        if removed == 0:
            raise ValueError("Inexistent student")
                    
    def updateStudentList(self, studentID, studentName):
        '''
        Function that updates the name of a student based on its ID
        '''
        updated = 0
        index = 0
        while index < len(self.list):
            if studentID == self.list[index].getStudentID():
                self.list[index].setStudentName(studentName)
                updated = 1
            index += 1
            
        if updated == 0:
            raise ValueError("Inexistent value")
        
    def findStudentByID(self, studentID):
        '''
        Function that returns the index of a student in the list, based on its ID
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getStudentID()== studentID:
                return index
        return -1
    
    def findStudentNameByID(self, studentID):
        '''
        Function that returns the name of a student in the list, based on its ID
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getStudentID()== studentID:
                return self.list[index].getStudentName()
        return -1
    
    def existsStudent(self, studentID):
        '''
        Function that checks whether or not a student exists
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getStudentID() == studentID:
                return True
        return False
        
    def getStudentList(self):
        '''
        Function that returns a copy of the student list
        '''
        return self.list[:]
    
    def getStudentIDList(self):
        '''
        Function that returns a list with the IDs of all disciplines
        '''
        studentIDList = []
        for student in self.list:
            studentID = student.getStudentID()
            studentIDList.append(studentID)
            
        return studentIDList
    
    def printStudents(self):
        '''
        Function that prints all student data
        '''
        for index in range(0, len(self.list)):
            print(str(self.list[index]))
            
class TestStudentRepo(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testAddStudent(self):
        studentToAdd = student(1, "Oana")
        studentList = studentRepo()
        studentList.addStudent(studentToAdd)
        assert studentList.list == [studentToAdd]
        
    def testRemoveStudent(self):
        studentList = studentRepo()
        studentToAdd = student(1, "Oana")
        studentList.addStudent(studentToAdd)
        studentToAdd = student(2, "Oana2")
        studentList.addStudent(studentToAdd)
        studentList.removeStudent(1)
        assert studentList.list == [studentToAdd]
        
    def testUpdateStudent(self):
        studentList = studentRepo()
        studentToAdd = student(1, "Oana")
        studentList.addStudent(studentToAdd)
        studentToAdd = student(2, "Oana2")
        studentList.addStudent(studentToAdd)
        studentList.updateStudentList(2, "Nourica")
        assert studentList.list[1].getStudentName() == "Nourica"
        
    def testFindStudentByID(self):
        studentList = studentRepo()
        studentToAdd = student(1, "Oana")
        studentList.addStudent(studentToAdd)
        studentToAdd = student(2, "Oana2")
        studentList.addStudent(studentToAdd)
        index = studentList.findStudentByID(2)
        assert index == 1
        index = studentList.findStudentByID(3)
        assert index == -1
        
    def testExistsStudent(self):
        studentList = studentRepo()
        studentToAdd = student(1, "Oana")
        studentList.addStudent(studentToAdd)
        studentToAdd = student(2, "Oana2")
        studentList.addStudent(studentToAdd)
        index = studentList.findStudentByID(2)
        assert index == 1
        index = studentList.findStudentByID(3)
        assert index == -1
        
    def testGetStudentIDList(self):
        studentList = studentRepo()
        studentToAdd = student(1, "Oana")
        studentList.addStudent(studentToAdd)
        studentToAdd = student(2, "Oana2")
        studentList.addStudent(studentToAdd)
        IDList = studentList.getStudentIDList()
        assert IDList == [1, 2]