from repository import *
from sentence import *

class Service:
    def __init__(self, repo):
        self.__repo = repo
        self.__undo = Sentence("") #Here we store the last performed operation
        self.__sentence = self.__repo.pickRandomSentence()
        self.__shuffled = self.__sentence.scramble()
        self.__score = self.__sentence.getScore()
    
    def getScore(self):
        '''
        Function that returns score
        '''
        return self.__score
    
    def getShuffled(self):
        '''
        Function that returns the scrambled sentence
        '''
        return self.__shuffled
    
    def getSentence(self):
        '''
        Function that returns the original sentence
        '''
        return self.__sentence
    
    def setShuffled(self, string):
        '''
        Function used for modifying the current state of the shuffled sentence
        '''
        self.__shuffled = Sentence(string)
        
    def setUndo(self):
        '''
        Function used for setting the last performed operation
        '''
        self.__undo = str(self.getShuffled())

    def getValidIndexes(self):
        '''
        Function that finds the valid indexes for each word in the sentence.
        Output: indexes - a list of lists, corresponding to each word in the sentence, in order (the index of an element, corresponds to the index of the word)
        '''
        words = self.__sentence.getWords()
        indexes = []
        for word in words:
            wordIndexes = []
            for i in range (1, len(word)-1):
                wordIndexes.append(i)
                
            indexes.append(wordIndexes)
            
        return indexes
        
    def undo(self):
        '''
        Function that allows undoing last performed swap
        '''
        if self.__undo != "":
            self.setShuffled(self.__undo)
            self.__undo = ""
            return True
            
        else:
            print("No undo left")
            return False
        
    def decreaseScore(self):
        '''
        Function that decreases the score
        '''
        self.__score -= 1
        
    def isWon(self):
        '''
        Function that checks whether the game has been won or not, by comparing the scrambled sentence to the original one.
        Return True if the two sentences are identical, returns False otherwise
        '''
        if str(self.__sentence) == str(self.__shuffled):
            return True
        
        return False
    
    def swap(self, w1, l1, w2, l2):
        '''
        Function that swaps 2 letters in 2 different words or inside the same word.
        Input: w1 - the index of the first word
               l1 - the index of the letter from the first word
               w2 - the index of the second word
               l2 - the index of the letter from the second word
        Output: sentence - a string containing the updated sentence 
        '''
        
        words = self.__shuffled.getWords()
        
        aux1 = words[w1][l1]
        aux2 = words[w2][l2]
        
        word = ""
        for i in range(0, len(words[w1])):
            if i != l1:
                word += words[w1][i]
            else:
                word += aux2
                
        words[w1] = word
        
        word = ""
        for i in range(0, len(words[w2])):
            if i != l2:
                word += words[w2][i]
            else:
                word += aux1
                
        words[w2] = word
                
        sentence = ""
        for word in words:
            sentence += word
            sentence += ' '
            
        return sentence
    
class testService(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testGetValidIndexes(self):
        repository = Repository("testingInput.txt")
        service = Service(repository)
        
        print(service.getSentence())
        indexes = service.getValidIndexes()
        assert indexes == [[1, 2, 3]]        
        
    def testGetScore(self):
        repository = Repository("testingInput.txt")
        service = Service(repository)
        assert service.getScore() == 5
        
    def testDecreaseScore(self):
        repository = Repository("testingInput.txt")
        service = Service(repository)
        assert service.getScore() == 5
        
        service.decreaseScore()
        assert service.getScore() == 4
        
    def testIsWon(self):
        repository = Repository("testingInput.txt")
        service = Service(repository)
        
        service.setShuffled(str(service.getSentence()))
        
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)    