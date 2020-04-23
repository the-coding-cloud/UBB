from studentRepo import *
from disciplineRepo import *
from gradeRepo import *
from business import *

class console:
    
    def __init__(self, studentList, disciplineList, gradeList, undoRedoController):
        self.studentList = studentList
        self.disciplineList = disciplineList
        self.gradeList = gradeList
        self.undoRedoController = undoRedoController
        
    def uiAddStudent(self):
        try:
            studentID = int(input("Student ID:"))
        except:
            ValueError ("Invalid ID")
        studentName = input("Student name:")
        self.studentList.addNewStudent(studentID, studentName)

    def uiAddDiscipline(self):
        try:
            disciplineID = int(input("Discipline ID:"))
        except:
            ValueError ("Invalid ID")
        disciplineName = input("Discipline name:")
        self.disciplineList.addNewDiscipline(disciplineID, disciplineName)
    
    def uiAddGrade(self):
        try:
            disciplineID = int(input("Discipline ID:"))
            studentID = int(input("Student ID:"))
        except:
            ValueError ("Invalid ID")
        try:
            gradeValue = float(input("Grade value:"))
        except:
            ValueError ("Invalid float value")
        if self.studentList.repo.existsStudent(studentID) and self.disciplineList.repo.existsDiscipline(disciplineID) and gradeValue > 0 and gradeValue <=10:
            self.gradeList.addNewGrade(disciplineID, studentID, gradeValue)
        else:
            raise ValueError ("Invalid grade info")
        
    def uiChangeStudentName(self):
        try:
            studentID = int(input("Student ID:"))
        except:
            ValueError ("Invalid ID")
        studentName = input("Student name:")
        self.studentList.updateStudent(studentID, studentName)
    
    def uiChangeDisciplineName(self):
        try:    
            disciplineID = int(input("Discipline ID:"))
        except:
            ValueError ("Invalid ID")
        disciplineName = input("Discipline name:")
        self.disciplineList.updateDiscipline(disciplineID, disciplineName)
    
    def uiListAllStudents(self):
        self.studentList.printAllStudents()
    
    def uiListAllDisciplines(self):
        self.disciplineList.printAllDisciplines()
    
    def uiRemoveStudent(self):
        try:
            studentID = int(input("Student ID:"))
        except:
            ValueError ("Invalid ID")
        
        self.studentList.removeStudent(studentID)
        self.gradeList.removeGradesByStudentID(studentID)
    
    def uiRemoveDiscipline(self):
        try:
            disciplineID = int(input("Discipline ID:"))
        except:
            ValueError ("Invalid ID")
            
        self.disciplineList.removeDiscipline(disciplineID)
        self.gradeList.removeGradesByDisciplineID(disciplineID)
        
    def uiSearchStudent(self):
        inputString = input("Enter student ID/name:")
        searchResults = self.studentList.searchStudent(inputString)
        if len(searchResults) > 0:
            for studentID in searchResults:
                self.studentList.printStudentByID(int(studentID))
        else:
            print("No matching results")
            
    def uiSearchDiscipline(self):
        inputString = input("Enter discipline ID/name:")
        searchResults = self.disciplineList.searchDiscipline(inputString)
        if len(searchResults) > 0:
            for disciplineID in searchResults:
                self.disciplineList.printDisciplineByID(int(disciplineID))
        else:
            print("No matching results")
    
    def uiSortStudentsAlphabetically(self):
        try:
            disciplineID = int(input("Enter discipline ID:"))
        except:
            ValueError ("Invalid ID")
        listOfStudentsID = self.gradeList.findStudentsAtDiscipline(disciplineID)
        listOfStudents = self.studentList.sortStudentsAlphabetically(listOfStudentsID)
        for student in listOfStudents:
            self.studentList.printStudentByID(student[0])
            
    def uiSortStudentByAverage(self):
        try:
            disciplineID = int(input("Enter discipline ID:"))
        except:
            ValueError ("Invalid ID")
        listOfStudentsID = self.gradeList.findStudentsAtDiscipline(disciplineID)
        listOfStudents = self.gradeList.sortStudentsByAverage(listOfStudentsID, disciplineID)
        for student in listOfStudents:
            self.studentList.printStudentByID(student[0])
            print ("Average grade: "+ str(student[1]))
            
    def uiFindFailingStudents(self):
        studentIDList = self.studentList.repo.getStudentIDList()
        disciplineIDList = self.disciplineList.repo.getDisciplineIDList()
        failingStudents = self.gradeList.findFailingStudents(studentIDList, disciplineIDList)
        if len(failingStudents) > 0:
            for student in failingStudents:
                self.studentList.printStudentByID(student[0])
                print ("Average grade: "+ str(student[1]))
        else:
            print("No failing students")
            
    def uiFindBestStudents(self):
        studentIDList = self.studentList.repo.getStudentIDList()
        disciplineIDList = self.disciplineList.repo.getDisciplineIDList()
        bestStudents = self.gradeList.findBestStudents(studentIDList, disciplineIDList)
        for student in bestStudents:
            self.studentList.printStudentByID(student[0])
            print ("Average grade: "+ str(student[1]))
    
    def uiFindBestDisciplines(self):
        studentIDList = self.studentList.repo.getStudentIDList()
        disciplineIDList = self.disciplineList.repo.getDisciplineIDList()
        bestDisciplines = self.gradeList.findBestDisciplines(studentIDList, disciplineIDList)
        for discipline in bestDisciplines:
            self.disciplineList.printDisciplineByID(discipline[0])
            print ("Average grade: "+ str(discipline[1]))
        
    def uiPrintGrades(self):
        self.gradeList.repo.printGrades()
        
    def uiUndo(self):
        self.undoRedoController.undo()
        
    def uiRedo(self):
        self.undoRedoController.redo()
      
    def printMenu(self):
        print("Choose one of the following actions by entering only the number of the command:")
        print("1. Add a new student")
        print("2. Add a new discipline")
        print("3. Grade a student")
        print("4. Remove a student")
        print("5. Remove a discipline")
        print("6. Update student name")
        print("7. Update discipline name")
        print("8. List all students")
        print("9. List all disciplines")
        print("10. Search student")
        print("11. Search discipline")
        print("12. Sort the students enrolled at a discipline alphabetically")
        print("13. Sort the students enrolled at a discipline descending by average grade")
        print("14. Print all the students failing at at least 1 discipline")
        print("15. Print the students with the best school situation, sorted in descending order by their aggregated average grade")
        print("16. Print all disciplines that have at least 1 grade, in descending order of the average grade received by all students")
        print("17. Print all grades")
        print("18. Undo")
        print("19. Redo")
        print("20. Exit")
        
    def run(self):
        '''
        self.studentList.addNewStudent(1, "Oana1", False)
        self.studentList.addNewStudent(2, "Oana6", False)
        self.studentList.addNewStudent(3, "Oana4", False)
        self.studentList.addNewStudent(4, "Oana3", False)
        self.studentList.addNewStudent(5, "Oana5", False)
        
        self.disciplineList.addNewDiscipline(1, "LC", False)
        self.disciplineList.addNewDiscipline(2, "FP", False)
        self.disciplineList.addNewDiscipline(3, "ASC", False)
        self.disciplineList.addNewDiscipline(4, "Alg", False)
        self.disciplineList.addNewDiscipline(5, "Analiza", False)
        
        self.gradeList.addNewGrade(1, 1, 10, False)
        self.gradeList.addNewGrade(1, 2, 9, False)
        self.gradeList.addNewGrade(1, 3, 9, False)
        self.gradeList.addNewGrade(1, 3, 10, False)
        self.gradeList.addNewGrade(2, 1, 10, False)
        self.gradeList.addNewGrade(2, 2, 9, False)
        self.gradeList.addNewGrade(2, 3, 8, False)
        self.gradeList.addNewGrade(3, 1, 10, False)
        self.gradeList.addNewGrade(3, 2, 9, False)
        self.gradeList.addNewGrade(3, 3, 8, False)
        self.gradeList.addNewGrade(4, 1, 4, False)
        '''
        
        for i in range (1, 101):
            self.studentList.addNewStudent(i, "Oana"+str(i), False)
        
        for i in range (1, 101):
            self.disciplineList.addNewDiscipline(i, "Discipline"+str(i), False)
        
        for i in range (1, 11):
            for j in range (1, 11):
                for grade in range(5, 11):
                    self.gradeList.addNewGrade(i, j, grade, False)
                    
        commands = {"1" : self.uiAddStudent,
                    "2" : self.uiAddDiscipline,
                    "3" : self.uiAddGrade, 
                    "4" : self.uiRemoveStudent,
                    "5" : self.uiRemoveDiscipline,
                    "6" : self.uiChangeStudentName,
                    "7" : self.uiChangeDisciplineName, 
                    "8" : self.uiListAllStudents, 
                    "9" : self.uiListAllDisciplines,
                    "10": self.uiSearchStudent,
                    "11": self.uiSearchDiscipline,
                    "12": self.uiSortStudentsAlphabetically,
                    "13": self.uiSortStudentByAverage,
                    "14": self.uiFindFailingStudents,
                    "15": self.uiFindBestStudents,
                    "16": self.uiFindBestDisciplines,
                    "17": self.uiPrintGrades,
                    "18": self.uiUndo,
                    "19": self.uiRedo}
                    
        self.printMenu()
        
        while True:
            command = input("Please give a valid command:")
            if command == "20":
                return 
            try:
                if command in commands:
                    commands[command]()
            except ValueError as ve:
                print(str(ve))