from sentence import *
from random import *
import unittest

class Repository():
    def __init__(self, fileName):
        self.__list = []
        self.__fileName = fileName
        self.loadFromFile()
        
    def getList(self):
        '''
        Function only used for testing later
        '''
        return self.__list[:]
        
    def loadFromFile(self):
        '''
        Function used for initialising the repository. Reads line by line from the file and stores each sentence as a Sentence object,
        as an element inside a list
        '''
        try:
            file = open(self.__fileName, "r")
            line = file.readline().strip()
            while line != "":
                self.__list.append(Sentence(line))
                line = file.readline().strip()
            
        except IOError:
            pass
        
        finally:
            file.close()
            
    def pickRandomSentence(self):
        '''
        Function that randomly picks a sentence from the repository.
        Output: a Sentence object 
        '''
        index = randint(0, len(self.__list)-1)
        return self.__list[index]

        
class testRepository(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testLoadFromFile(self):
        repository = Repository("testingInput.txt")
        testList = repository.getList()
        
        assert len(testList) == 3
        assert str(testList[0]) == "Test1"        
        
    def testPickRandomSentence(self):
        repository = Repository("testingInput.txt")
        sentence = repository.pickRandomSentence()
        
        assert sentence in repository.getList()
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
          
    