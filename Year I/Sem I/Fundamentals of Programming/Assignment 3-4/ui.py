from functions import *

def extendUndoList(listOfApartments, undoList):
    listToAppend = []
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for apartment in listOfApartments:
        apartmentNumber = getApartmentNumber(apartment)
        expenseType = "water"
        expenseValue = getExpenseValue(apartment, expenseType)
        newApartment = createApartment(apartmentNumber, expenseType, expenseValue)
        for expenseType in expenseTypes:
            expenseValue = getExpenseValue(apartment, expenseType)
            setExpenseValue(newApartment, expenseType, expenseValue)
            
        addElementToList(listToAppend, newApartment)
    undoList.append(listToAppend)

def ui_addApartment(listOfApartments, commandElements, undoList):
    if len(commandElements) == 3:
        try:
            apartmentNumber = int(commandElements[0])
            expenseType = commandElements[1]
            expenseValue = int(commandElements[2])
            apartment = createApartment(apartmentNumber, expenseType, expenseValue)
            validateApartment(apartment)
            extendUndoList(listOfApartments, undoList)
            addApartment(listOfApartments, apartment, expenseType, expenseValue)
        except ValueError:
            print("Invalid apartment number/expense value")
    else:
        print ("Invalid number of parameters")
        return
        
def ui_removeExpenses(listOfApartments, commandElements, undoList):  
    if len(commandElements) == 3 and commandElements[1] == "to":
        try:         
            firstApartmentNumber = int(commandElements[0])
            lastApartmentNumber = int(commandElements[2])
            if firstApartmentNumber > lastApartmentNumber:
                raise ValueError ("Invalid apartment numbers")
        except ValueError:
            print ("Invalid apartment numbers")
        else:
            extendUndoList(listOfApartments, undoList)
            removeExpensesApartmentRange(listOfApartments, firstApartmentNumber, lastApartmentNumber)
    elif len(commandElements) == 1:
        expenseTypes = ["water", "heating", "electricity", "gas", "other"]
        if commandElements[0] in expenseTypes:
            extendUndoList(listOfApartments, undoList)
            removeExpensesByType(listOfApartments, commandElements[0])
        else:
            try:
                apartmentNumber = int(commandElements[0])
                index = searchByApartmentNumber(listOfApartments, apartmentNumber)
                if index < 0:
                    raise ValueError ("Inexistent element")
                else:
                    extendUndoList(listOfApartments, undoList)
                    removeExpensesApartment(listOfApartments[index])
            except ValueError:
                print("Invalid apartment number")
    else:
        print("Invalid command, try again")
        return

def ui_replaceExpenses(listOfApartments, commandElements, undoList):
    if len(commandElements) == 4 and commandElements[2] == "with":
        try:
            expenseTypes = ["water", "heating", "electricity", "gas", "other"]
            apartmentNumber = int(commandElements[0])
            expenseType = commandElements[1]
            expenseValue = int(commandElements[3])
            if expenseType in expenseTypes and expenseValue >= 0:
                extendUndoList(listOfApartments, undoList)
                replaceExpenses(listOfApartments, apartmentNumber, expenseType, expenseValue)
            else:
                print("Invalid command")
                return
        except ValueError:
            print ("Invalid apartment number or expense value")
    else:
        print("Invalid command")
        return

def ui_listExpenses(listOfApartments, commandElements):
    if len(commandElements) == 0:
        listAll(listOfApartments)
    elif len(commandElements) == 1:
        try:
            apartmentNumber = int(commandElements[0])
            index = searchByApartmentNumber(listOfApartments, apartmentNumber)
            if index < 0:
                raise ValueError("Inexistent element")
            else:
                listApartment(listOfApartments[index])
        except ValueError:
            print ("Invalid apartment number")
    elif len(commandElements) == 2:
        try:
            compareSign = commandElements[0]
            totalExpensesValue = int(commandElements[1])
            if compareSign in ["<", "=", ">"] and totalExpensesValue >= 0:
                listSelectedApartments(listOfApartments, compareSign, totalExpensesValue)
            else:
                raise ValueError ("Invalid command")
        except ValueError:
            print ("Invalid value number")
    else:
        raise ValueError ("Invalid number of parameters")
    
def ui_sumByExpenseType(listOfApartments, commandElements):
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    expenseType = commandElements[0]
    if expenseType in expenseTypes and len(commandElements) == 1:
        print(sumByExpenseType(listOfApartments, expenseType))
    else:
        raise ValueError ("Invalid command")

def ui_maxExpense(listOfApartments, commandElements):
    apartmentNumber = int(commandElements[0])
    if len(commandElements) == 1:
        print(maxExpense(listOfApartments, apartmentNumber))
    else:
        raise ValueError ("Invalid number of parameters")

def ui_sort(listOfApartments, commandElements):
    if commandElements[0]=="type" and len(commandElements)==1:
        listOfTotalExpenseValues = sortType(listOfApartments)
        print_sortType(listOfTotalExpenseValues)
    elif commandElements[0]=="apartment" and len(commandElements)==1:
        listOfTotalExpenseValues = sortApartment(listOfApartments)
        print_sortApartment(listOfTotalExpenseValues)
    else:
        raise ValueError("Invalid command")

def ui_filterList(listOfApartments, commandElements, undoList):
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    if len(commandElements) == 1:
        if commandElements[0] in expenseTypes:
            extendUndoList(listOfApartments, undoList)
            filterType(listOfApartments, commandElements[0])
        else:
            try:
                expenseValue = int(commandElements[0])
                if expenseValue < 0:
                    print("You have entered a negative number. That's a bit strange. Try again with a positive integer")
                    return
                else:
                    extendUndoList(listOfApartments, undoList)
                    filterValue(listOfApartments, expenseValue)
            except ValueError:
                print("Invalid command")
    else:
        raise ValueError("Invalid number of parameters.")