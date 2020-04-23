from disciplineRepo import *
from gradeRepo import *
from studentRepo import *
from business import *
from console import *
from undoController import *

studentRepo = studentRepo()
disciplineRepo = disciplineRepo()
gradeRepo = gradeRepo()
undoRedoController = UndoControl()
studentList = business(studentRepo, undoRedoController)
disciplineList = business(disciplineRepo, undoRedoController)
gradeList = business(gradeRepo, undoRedoController)
console = console(studentList, disciplineList, gradeList, undoRedoController)
console.run()