def createApartment (apartmentNumber, expenseType, expenseValue):
    '''
    Function that creates a new apartment entry for the list
    Input: apartmentNumber, expenseType, expenseValue
    Preconditions: apartmentNumber - positive integer, expenseType - string, expenseValue - positive integer
    Output: apartment
    Postconditions: apartment - dictionary containing the initial details corresponding to a certain apartment
    '''
    apartment = {"Apartment number": apartmentNumber, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    if expenseType not in expenseTypes:
        raise ValueError("Invalid expense type")
    else:
        apartment[expenseType] = expenseValue
        return apartment
    
def validateApartment (apartment):
    '''
    Function that validates a new apartment entry
    Input: apartment
    Preconditions: apartment - dictionary
    Output: raises ValueError in case of invalid data
    '''
    errors = ""
    if apartment["Apartment number"] < 0:
        errors+="Invalid apartment number!\n"  
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for expenseType in expenseTypes:
        if apartment[expenseType] < 0:
            errors+="Invalid expense value!\n"
    if len(errors)>0:
        raise ValueError(errors)
    
def getApartmentNumber(apartment):
    '''
    Function that returns the apartment number of an apartment
    Input: apartment
    Preconditions: apartment - dictionary
    Output: apartment number
    Postconditions: apartment number - positive integer
    '''
    return apartment["Apartment number"]

def getTotalApartmentExpenses(apartment):
    '''
    Function that returns the total expenses of an apartment
    Input: apartment
    Preconditions: apartment - dictionary
    Output: totalAptExpenses
    Postconditions: totalAptExpenses - positive integer representing the sum of all expenses of the given apartment
    '''
    totalAptExpenses = 0
    
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for expenseType in expenseTypes:
        totalAptExpenses = totalAptExpenses + apartment[expenseType]
        
    return totalAptExpenses

def setExpenseValue(apartment, expenseType, expenseValue):
    '''
    Function that sets the value of a certain expense of an apartment
    Input: apartment, expenseType, expenseValue
    Preconditions: apartment - dictionary, expenseType - string, expenseValue - positive integer
    '''
    apartment[expenseType] = expenseValue

def getExpenseValue(apartment, expenseType):
    '''
    Function that returns the value of the an expense of a certain apartment
    Input: apartment, expenseType
    Preconditions: apartment - positive integer, expenseType - string
    Output: expenseValue
    Postconditions: expenseValue - positive integer
    '''
    expenseValue = apartment[expenseType]
    return expenseValue

def isSameApartment(apartment1, apartment2):
    '''
    Function that verifies whether two apartments have the same number or not
    Input: apartment1, apartment2
    Preconditions: apartment1, apartment2 - dictionaries
    Output: True/False
    Postconditions: the function returns True if the apartments have the same number and False if the apartments have different numbers
    '''
    return getApartmentNumber(apartment1)==getApartmentNumber(apartment2)

def existsElementInList (listOfElements, elementToVerify, equals):
    '''
    Function (independent of the model) that verifies whether an element already exists in a list
    Input: listOfElements, element, equals 
    Preconditions: listOfElements - list, element - element to be verified, equals - function that verifies if two elements are the same
    Output: the function raises a ValueError if the element already exists
    '''
    for element in listOfElements:
        if equals (element, elementToVerify):
            raise ValueError ("Existing element")    
        
def searchElementInList(listOfElements, element, equals):
    '''
    Function that searches for a certain element in a list and returns its index
    Input: listOfElements, element, equals
    Preconditions: listOfElements - list, element - element to be searched, equals - function that verifies if two elements are the same
    Output: index of the element in listOfElements or -1 
    Postconditions: the functions returns the index of the element if the element is in the list or -1 if the element is not found in the list
    '''
    for index in range(len(listOfElements)):
        if equals(element, listOfElements[index]):
            return index
    return -1

def searchByApartmentNumber(listOfApartments, apartmentNumber):
    '''
    Function that returns the index of an apartment in listOfApartments, by knowing only the apartment number
    Input: listOfApartments, apartmentNumber
    Preconditions: listOfApartments - list, apartmentNumber - apartment
    Output: index of the apartment or -1
    Postconditions: the functions returns the index of the apartment if the apartmentNumber exists in the list or -1 if the apartmentNumber is not found in the list
    '''
    for index in range(len(listOfApartments)):
        if getApartmentNumber(listOfApartments[index]) == apartmentNumber:
            return index
    return -1
    
def addElementToList (listOfElements, element):
    '''
    Function (independent of the model) that adds an element to a list
    Input: listOfElements, element
    Preconditions: listOfElements - list, element - an object of the same type as the other elements in the list
    Output: the list is modified by appending the new element
    '''
    listOfElements.append(element)
    
def getAllList(listOfElements):
    '''
    Function that returns a copy of the list
    Input: listOfElements
    Preconditions: listOfElements - list
    Output: listOfElements[:]
    Postconditions: the returned list is only a copy of the initial list
    '''
    return listOfElements[:]    

def toStringApartment(apartment):
    '''
    Function that returns a string with all the details of an apartment
    Input: apartment
    Preconditions: apartment - dictionary
    Output: strApartment
    Postconditions: strApartment - string
    '''
    strApartment=""
    strApartment += ("Apartment: "+str(apartment["Apartment number"]))
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for expenseType in expenseTypes:
        strApartment += "\n\t"+str(expenseType)+": "+str(apartment[expenseType])
    
    return strApartment

def addApartment(listOfApartments, apartment, expenseType, expenseValue):
    '''
    Function that add a new apartment to the list or adds a new expense to an existing apartment
    Input: listOfApartments, apartment, expenseType, expenseValue
    Preconditions: listOfApartments - list of apartments, apartment - dictionary, expenseType - string, expenseValue - positive integer
    Output: raises a ValueError if the input data is not valid
    '''
    index = searchElementInList(listOfApartments, apartment, isSameApartment)
    if index < 0:
        addElementToList (listOfApartments, apartment)
    else:
        if getExpenseValue(listOfApartments[index], expenseType) == 0:
            setExpenseValue(listOfApartments[index], expenseType, expenseValue)
        else:
            raise ValueError ("There is already a value for this apartment, try the replace command instead")
        
def removeExpensesApartment(apartment):
    '''
    Function that removes all the expenses of an apartment
    Input: apartment
    Preconditions: apartment - dictionary
    Output: -
    Postconditions: the values of all expenses is 0
    '''
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for expenseType in expenseTypes:
        setExpenseValue(apartment, expenseType, 0)
        
def removeExpensesApartmentRange (listOfApartments, firstapartmentNumber, lastapartmentNumber):
    '''
    Function that removes all the expenses of the apartments in a certain range
    Input: listOfApartments, firstapartmentNumber, lastapartmentNumber
    Preconditions: listOfApartments - list of the apartments,
                   firstapartmentNumber - positive integer representing the first apartment in the range, 
                   lastapartmentNumber - positive integer representing the last apartment in the range
    Output: - 
    Postconditions: all the apartments in the range will have their expenses changed to 0
    '''
    for apartment in listOfApartments:
        if getApartmentNumber(apartment)>=firstapartmentNumber and getApartmentNumber(apartment)<=lastapartmentNumber:
            removeExpensesApartment(apartment)
            
def removeExpensesByType (listOfApartments, expenseType):
    '''
    Function that remove all the expenses for a certain expense type from all apartments
    Input: listOfApartments, expenseType
    Preconditions: listOfApartments - list of apartments, expenseType - string
    Output: - 
    Postconditions: all the expenses for a certain expense type from all apartments have the value equal to 0
    '''
    for apartment in listOfApartments:
        setExpenseValue(apartment, expenseType, 0)
        
def replaceExpenses(listOfApartments, apartmentNumber, expenseType, expenseValue):
    '''
    Function that replaces the amount of the expense with a certain type for an apartment having the given apartment number with a new value
    Input: listOfApartments, apartmentNumber, expenseType, expenseValue
    Preconditions: listOfApartments - list, apartmentNumber - positive integer, expenseType - string, expenseValue - positive integer
    Output: raises ValueError if the input data is invalid
    Postconditions:
    '''
    index = searchByApartmentNumber(listOfApartments, apartmentNumber)
    if index < 0:
        raise ValueError ("Inexistent element!")   
    setExpenseValue(listOfApartments[index], expenseType, expenseValue)

def listApartment (apartment):
    '''
    Function that lists all the details of an apartment
    Input: apartment
    Preconditions: apartment - dictionary
    Output: 
    Postconditions:
    '''
    print(toStringApartment(apartment))
    
def listAll (listOfApartments):
    '''
    Function that lists the details for all apartments in the list
    Input: listOfApartments
    Preconditions: listOfApartments - list of apartments
    Output: 
    Postconditions:
    '''
    for apartment in listOfApartments:
        listApartment(apartment)


def listSelectedApartments (listOfApartments, compareSign, totalExpensesValue):
    '''
    Function that lists the details only for the apartments fulfilling certain criteria
    Input: listOfApartments, compareSign, totalExpensesValue
    Preconditions: listOfApartments - list of apartments,
                   compareSign - one of the symbols "<", ">" or "=",
                   totalExpensesValue - positive integer
    Output: prints the requested apartments
    Postconditions:
    '''
    selectedApartments = "Apartment number(s):"
    initialStrLen = len(selectedApartments)
    if compareSign == ">":
        for apartment in listOfApartments:
            totalAptExpenses = getTotalApartmentExpenses(apartment)
            if totalAptExpenses > totalExpensesValue:
                selectedApartments += " " + str(apartment["Apartment number"])
        if len(selectedApartments) > initialStrLen:
            print(selectedApartments)
        else:
            print("No apartments to list")
    elif compareSign == "<":
        for apartment in listOfApartments:
            totalAptExpenses = getTotalApartmentExpenses(apartment)
            if totalAptExpenses < totalExpensesValue:
                selectedApartments += " " + str(apartment["Apartment number"])
        if len(selectedApartments) > initialStrLen:
            print(selectedApartments)
        else:
            print("No apartments to list")       
    
    elif compareSign == "=":
        for apartment in listOfApartments:
            totalAptExpenses = getTotalApartmentExpenses(apartment)
            if totalAptExpenses == totalExpensesValue:
                selectedApartments += " " + str(apartment["Apartment number"])
        if len(selectedApartments) > initialStrLen:
            print(selectedApartments)
        else:
            print("No apartments to list")
    
    else:
        print ("Invalid command, try again")
        return
    
def sumByExpenseType(listOfApartments, expenseType):
    '''
    Function that computes the total value for a certain expense type for the whole list of apartments
    Input: listOfApartments, expenseType
    Preconditions: listOfApartments - list of apartments,
                   expenseType - string
    Output: totalExpenseValue
    Postconditions: totalExpenseValue - positive integer
    '''
    totalExpenseValue = 0
    for apartment in listOfApartments:
        expenseValue = getExpenseValue(apartment, expenseType)
        totalExpenseValue += expenseValue
    
    return totalExpenseValue

def maxExpense(listOfApartments, apartmentNumber):
    '''
    Function that returns the expense type with the highest value and its value for a given apartment
    Input: listOfApartments, apartmentNumber
    Preconditions: listOfApartments - list of apartments,
                   apartmentNumber - positive integer
    Output: totalExpenseValue
    Postconditions: totalExpenseValue - positive integer
    '''
    index = searchByApartmentNumber(listOfApartments, apartmentNumber)
    maxExpenseType = "water"
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    if index >= 0:
        for expenseType in expenseTypes:
            if listOfApartments[index][expenseType] > listOfApartments[index][maxExpenseType]:
                maxExpenseType = expenseType
        if getExpenseValue(listOfApartments[index], maxExpenseType) > 0:
            return "The highest expense of apartment "+str(getApartmentNumber(listOfApartments[index]))+" is "+str(maxExpenseType)+" with a value of "+str(getExpenseValue(listOfApartments[index], maxExpenseType))
    else:
        raise ValueError ("The apartment does not exist")
    
def getTotalExpenseTypeValue(totalExpenseTypeValue):
    return totalExpenseTypeValue[1]


       
def sortType(listOfApartments):
    '''
    Function that returns the total amount of expenses for each type, sorted ascending by amount of money
    Input: listOfApartments
    Preconditions: listOfApartments - list of apartments,
    Output: listOfTotalExpenseValues
    Postconditions: listOfTotalExpenseValues - the total amount of expenses for each type, sorted ascending by amount of money
    '''
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    listOfTotalExpenseValues = []
    for expenseType in expenseTypes:
        totalExpenseTypeValue = sumByExpenseType(listOfApartments, expenseType)
        listOfTotalExpenseValues.append([expenseType, totalExpenseTypeValue])
    listOfTotalExpenseValues.sort(key=getTotalExpenseTypeValue, reverse=False)
    return listOfTotalExpenseValues
    
def getTotalApartmentExpenseValue(totalApartmentExpenses):
    return totalApartmentExpenses[1]

def print_sortType(listOfTotalExpenseValues):
    message = ""
    for totalExpenseValue in listOfTotalExpenseValues:
        message += str(totalExpenseValue[0])+": "+str(totalExpenseValue[1])+"\n"
    print(message)
    
def sortApartment(listOfApartments):
    '''
    Function that returns the list of apartments sorted ascending by total amount of expenses
    Input: listOfApartments
    Preconditions: listOfApartments - list of apartments,
    Output: totalExpenseValue
    Postconditions: totalExpenseValue - the list of apartments sorted ascending by total amount of expenses
    '''
    listOfTotalApartmentExpenses = []
    for apartment in listOfApartments:
        totalApartmentExpenses = getTotalApartmentExpenses(apartment)
        listOfTotalApartmentExpenses.append([getApartmentNumber(apartment), totalApartmentExpenses])
    listOfTotalApartmentExpenses.sort(key=getTotalApartmentExpenseValue, reverse=False)
    return listOfTotalApartmentExpenses
    
def print_sortApartment(listOfTotalApartmentExpenses):    
    message = ""
    for totalApartmentExpenseValue in listOfTotalApartmentExpenses:
        message += "Apartment no."+str(totalApartmentExpenseValue[0])+": "+str(totalApartmentExpenseValue[1])+"\n"
    print(message)
    
def filterType(listOfApartments, filterExpenseType):
    '''
    Function that only keeps the expenses of a certain type, setting all the other values to 0
    Input: listOfApartments, filterExpenseType
    Preconditions: listOfApartments - list of apartments
                   filterExpenseType - string representing an expense type
    '''
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for apartment in listOfApartments:
        for expenseType in expenseTypes:
            if expenseType != filterExpenseType:
                setExpenseValue(apartment, expenseType, 0)
'''
def filterValue(listOfApartments, totalExpenseValue):
    newApartmentList = []
    for apartment in listOfApartments:
        totalApartmentExpenses = getTotalApartmentExpenses(apartment)
        if totalApartmentExpenses < totalExpenseValue:
            newApartmentList.append(apartment)
    listOfApartments.clear()
    listOfApartments.extend(newApartmentList)
'''

def filterValue(listOfApartments, expenseValue):
    '''
    Function that only keeps the expenses smaller than a given amount, setting all the other values to 0
    Input: listOfApartments, expenseValue
    Preconditions: listOfApartments - list of apartments
                   expenseValue - positive integer
    '''
    expenseTypes = ["water", "heating", "electricity", "gas", "other"]
    for apartment in listOfApartments:
        for expenseType in expenseTypes:
            if getExpenseValue(apartment, expenseType) >= expenseValue:
                setExpenseValue(apartment, expenseType, 0)