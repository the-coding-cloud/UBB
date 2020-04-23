from ui import *
from functions import *    
from tests import *

def run_tests():
    test_createApartment()
    test_validateApartment()
    test_getApartmentNumber()
    test_getTotalApartmentExpenses()
    test_setExpenseValue()
    test_getExpenseValue()
    test_isSameApartment()
    test_existsElementInList()
    test_searchElementInList()
    test_searchByApartmentNumber()
    test_addElementToList()
    test_getAllList()
    test_removeExpensesApartment()
    test_removeExpensesApartmentRange()
    test_removeExpensesByType()
    test_replaceExpenses()
    test_sumByExpenseType()
    test_maxExpense()
    test_filterType()
    test_filterValue()
    
def run():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        #{"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        #{"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        #{"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        #{"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        #{"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    undoList = []
    commands = {"add": ui_addApartment, "remove": ui_removeExpenses, "replace": ui_replaceExpenses, "list": ui_listExpenses, "sum": ui_sumByExpenseType, "max": ui_maxExpense, "sort": ui_sort, "filter": ui_filterList}
    commandMessage = "Possible commands:\n"
    commandMessage += "add <apartment> <type> <amount>\n"
    commandMessage += "remove <apartment>\n"
    commandMessage += "remove <start apartment> to <end apartment>\n"
    commandMessage += "replace <apartment> <type> with <amount>\n"
    commandMessage += "list\n"
    commandMessage += "list <apartment>\n"
    commandMessage += "list [ < | = | > ] <amount>"
    commandMessage += "sum <type>\n"
    commandMessage += "max <apartment>\n"
    commandMessage += "sort apartment\n"
    commandMessage += "sort type\n"
    commandMessage += "filter <type>\n"
    commandMessage += "filter <value>\n"
    commandMessage += "undo\n"
    print(commandMessage)
    
    while True:
        command = input("Enter command: ")
        commandElements = command.split(" ")
        if commandElements[0]=="exit":
            return
        elif commandElements[0]=="undo":
            if len(undoList) > 0:
                listOfApartments.clear()
                listOfApartments.extend(undoList[len(undoList)-1])
                undoList.pop()
            else:
                print("No undo moves. Do something")
        elif commandElements[0] in commands:
            try:
                if commandElements[0] in ["add", "remove", "replace", "filter"]:
                    commands[commandElements[0]](listOfApartments, commandElements[1:], undoList)
                else:
                    commands[commandElements[0]](listOfApartments, commandElements[1:])
            except ValueError as ve:
                print(ve)
        else:
            print("Invalid command!")
     
run_tests()       
run()