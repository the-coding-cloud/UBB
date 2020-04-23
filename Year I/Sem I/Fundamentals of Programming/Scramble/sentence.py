from random import *
import unittest

class Sentence:
    def __init__(self, string):
        self.__sentence = string.strip()
        self.__words = string.split(" ")
        
    def __str__(self):
        return self.__sentence
    
    def __len__(self):
        return len(self.__sentence)
    
    def getWords(self):
        '''
        Function that returns the list of words in a sentence
        '''
        return self.__words
    
    def getScore(self):
        '''
        Computes the score based on the numbers of letters in the sentence.
        Output: score - natural number
        '''
        score = len(self.__sentence) - len(self.__words) + 1
        return score
        
    def scramble(self):
        '''
        Function that does the scramble as required:
        - the first and last letter of each word is kept in place (as well as the spaces)
        - the rest of the letters are shuffled randomly, with the possibility of having letters shuffled between words
        
        Output: a Sentence object, composed from the new, scrambled sentence 
        '''
        letters = []
        
        for word in self.__words:
            for i in range(1, len(word)-1):
                letters.append(word[i])
                
        shuffle(letters)
    
        
        string = ""
        count = 0
        
        for i in range(0, len(self.__words)):
            for j in range(0, len(self.__words[i])):
                if j == 0:
                    string += self.__words[i][j]
                    
                elif j == len(self.__words[i])-1:
                    string += self.__words[i][j]
                    string += " "
                    
                else:
                    string += letters[count]
                    count += 1
                    
        return Sentence(string)
                    
class testSentence(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
        
    def testGetScore(self):
        sentence = Sentence("One two three")
        assert sentence.getScore() == 11
        
        sentence = Sentence("Four")
        assert sentence.getScore() == 4
        
    def testScramble(self):
        sentence = Sentence("Scramble")
        assert str(sentence.scramble()) != "Scramble"
        print (sentence.scramble())
        
        sentence = Sentence("No")
        print (sentence.scramble())
        assert str(sentence.scramble()) == "No"
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        