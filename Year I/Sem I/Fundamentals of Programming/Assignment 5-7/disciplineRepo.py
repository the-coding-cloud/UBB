from discipline import *
import unittest

class disciplineRepo:
    def __init__(self):
        self.list = []
        
    def __len__(self):
        return len(self.list)
    
    def addDiscipline(self, discipline):
        '''
        Function that adds a new discipline
        '''
        if discipline in self.list:
            raise ValueError("Existing discipline!")
        self.list.append(discipline)
            
    def removeDiscipline(self, disciplineID):
        '''
        Function that removes a discipline based on its ID
        '''
        removed = 0
        index = 0
        while index < len(self.list):
            if disciplineID == self.list[index].getDisciplineID():
                del self.list[index]
                removed = 1
                index -=1
            index += 1
            
        if removed == 0:
            raise ValueError("Inexistent discipline")
        
    def updateDisciplineList(self, disciplineID, disciplineName):
        '''
        Function that updates the name of a discipline based on its ID
        '''
        updated = 0
        index = 0
        while index < len(self.list):
            if disciplineID == self.list[index].getDisciplineID():
                self.list[index].setDisciplineName(disciplineName)
                updated = 1
            index += 1
            
        if updated == 0:
            raise ValueError("Inexistent discipline")

    def findDisciplineByID(self, disciplineID):
        '''
        Function that returns the index of a discipline based on its ID
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getDisciplineID() == disciplineID:
                return index
        return -1     
    
    def findDisciplineNameByID(self, disciplineID):
        '''
        Function that returns the name of a discipline in the list, based on its ID
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getDisciplineID()== disciplineID:
                return self.list[index].getDisciplineName()
        return -1
    
    def existsDiscipline(self, disciplineID):
        '''
        Function that checks if a discipline exists or not
        '''
        for index in range(0, len(self.list)):
            if self.list[index].getDisciplineID() == disciplineID:
                return True
        return False
      
    def getDisciplineList(self):
        '''
        Function that returns a copy of the discipline list
        '''
        return self.list[:]
    
    def getDisciplineIDList(self):
        '''
        Function that returns a list with the IDs of all disciplines
        '''
        disciplineIDList = []
        for discipline in self.list:
            disciplineID = discipline.getDisciplineID()
            disciplineIDList.append(disciplineID)
            
        return disciplineIDList
    
    def printDisciplines(self):
        '''
        Function that prints all disciplines
        '''
        for index in range(0, len(self.list)):
            print(str(self.list[index]))

class TestDisciplineRepo(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testAddDiscipline(self):
        disciplineToAdd = discipline(1, "Mate")
        disciplineList = disciplineRepo()
        disciplineList.addDiscipline(disciplineToAdd)
        assert disciplineList.list == [disciplineToAdd]
        
    def testRemoveDiscipline(self):
        disciplineList = disciplineRepo()
        disciplineToAdd = discipline(1, "Mate")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineToAdd = discipline(2, "Mate2")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineList.removeDiscipline(1)
        assert disciplineList.list == [disciplineToAdd]
        
    def testUpdateDiscipline(self):
        disciplineList = disciplineRepo()
        disciplineToAdd = discipline(1, "Mate")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineToAdd = discipline(2, "Mate2")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineList.updateDisciplineList(2, "Nourica")
        assert disciplineList.list[1].getDisciplineName() == "Nourica"
        
    def testFindDisciplineByID(self):
        disciplineList = disciplineRepo()
        disciplineToAdd = discipline(1, "Mate")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineToAdd = discipline(2, "Mate2")
        disciplineList.addDiscipline(disciplineToAdd)
        index = disciplineList.findDisciplineByID(2)
        assert index == 1
        index = disciplineList.findDisciplineByID(3)
        assert index == -1
        
    def testExistsDiscipline(self):
        disciplineList = disciplineRepo()
        disciplineToAdd = discipline(1, "Mate")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineToAdd = discipline(2, "Mate2")
        disciplineList.addDiscipline(disciplineToAdd)
        index = disciplineList.findDisciplineByID(2)
        assert index == 1
        index = disciplineList.findDisciplineByID(3)
        assert index == -1
        
    def testGetDisciplineIDList(self):
        disciplineList = disciplineRepo()
        disciplineToAdd = discipline(1, "Mate")
        disciplineList.addDiscipline(disciplineToAdd)
        disciplineToAdd = discipline(2, "Mate2")
        disciplineList.addDiscipline(disciplineToAdd)
        IDList = disciplineList.getDisciplineIDList()
        assert IDList == [1, 2]