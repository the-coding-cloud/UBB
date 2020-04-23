class Person:
    def __init__(self, name, age):
        self.__name = name
        self.__age = age 
    
    def getName(self):
        return self.__name
    
    def getAge(self):
        return self.__age
    
    def __str__(self):
        return self.__name + ";" + str(self.__age)
    
class PersonRepo:
    def __init__(self, filename):
        self.__filename = filename
        self.list = []
        self.loadFromFile()
        
    def getPersonList(self):
        return self.list[:]
    
    def addPerson(self, name, age):
        personToAdd = Person(name, age)
        self.list.append(personToAdd)
        self.writeToFile()
        
    def loadFromFile(self):
        try:
            f = open(self.__filename, "r")
            line = f.readline().strip()
            while line != "":
                att = line.split(";")
                self.addPerson(att[0], att[1])
                line = f.readline().strip()
            
        except IOError:
            print ("shit")
            
        finally:
            f.close()
            
    def writeToFile(self):
        f = open(self.__filename, "w")
        persons = self.getPersonList()
        
        for person in persons:
            f.write(str(person))
            f.write("\n")
            
        f.close()
        
    def printPersons(self):
        for person in self.list:
            print(str(person))
        
            
repo = PersonRepo("persons.txt")

repo.printPersons()