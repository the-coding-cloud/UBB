from functions import *

def test_createApartment():
    apartment = createApartment(21, "water", 30)
    assert apartment == {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    
def test_validateApartment():
    apartment = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    try:
        validateApartment(apartment)
        assert True
    except:
        assert False
        
    apartment = {"Apartment number": -21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    try:
        validateApartment(apartment)
        assert False
    except ValueError as ve:
        assert str(ve)=="Invalid apartment number!\n"
        
def test_getApartmentNumber():
    apartment = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    assert getApartmentNumber(apartment)==21
    
def test_getTotalApartmentExpenses():
    apartment = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    assert getTotalApartmentExpenses(apartment)==70
    
def test_setExpenseValue():
    apartment = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    setExpenseValue(apartment, "heating", 30)
    assert apartment == {"Apartment number": 21, "water": 30, "heating": 30, "electricity": 40, "gas": 0, "other": 0}
    
def test_getExpenseValue():
    apartment = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    assert getExpenseValue(apartment, "water")==30   

def test_isSameApartment():
    apartment1 = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    apartment2 = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    assert isSameApartment(apartment1, apartment2) == True
    
    apartment1 = {"Apartment number": 11, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    apartment2 = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 0, "gas": 0, "other": 0}
    assert isSameApartment(apartment1, apartment2) == False
    
def test_existsElementInList():
    apartment1 = {"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    apartment2 = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    listOfApartments = [{"Apartment number": 21, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    try:
        existsElementInList(listOfApartments, apartment2, isSameApartment)
        assert False
    except ValueError as ve:
        assert str(ve) == "Existing element"
    
    existsElementInList(listOfApartments, apartment1, isSameApartment)
    assert True 
    
def test_searchElementInList():
    apartment1 = {"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    apartment2 = {"Apartment number": 21, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
    listOfApartments = [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    index = searchElementInList(listOfApartments, apartment1, isSameApartment)
    assert index == 0
    index = searchElementInList(listOfApartments, apartment2, isSameApartment)
    assert index == -1
    
def test_searchByApartmentNumber():
    listOfApartments = [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    index = searchByApartmentNumber(listOfApartments, 20)
    assert index == 0
    index = searchByApartmentNumber(listOfApartments, 21)
    assert index == -1
    
def test_addElementToList():
    listOfElements = []
    element = 21
    addElementToList(listOfElements, element)
    assert listOfElements == [21]
    
def test_getAllList():
    listOfApartments = [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    assert getAllList(listOfApartments) == [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    
def test_removeExpensesApartment():
    listOfApartments = [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    removeExpensesApartment(listOfApartments[0])
    assert listOfApartments == [{"Apartment number": 20, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0}]
    
def test_removeExpensesApartmentRange():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
    removeExpensesApartmentRange(listOfApartments, 2, 5)
    assert listOfApartments == [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
def test_removeExpensesByType():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
    removeExpensesByType(listOfApartments, "water")
    assert listOfApartments == [
        {"Apartment number": 1, "water": 0, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 0, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 0, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
def test_replaceExpenses():
    listOfApartments = [{"Apartment number": 20, "water": 30, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    replaceExpenses(listOfApartments, 20, "water", 65)
    assert listOfApartments == [{"Apartment number": 20, "water": 65, "heating": 0, "electricity": 40, "gas": 0, "other": 0}]
    
def test_sumByExpenseType():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
        ]
    assert sumByExpenseType(listOfApartments, "electricity") == 240
    
def test_maxExpense():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0}
        ]
    assert maxExpense(listOfApartments, 1) == "The highest expense of apartment 1 is electricity with a value of 200"

def test_filterType():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
    filterType(listOfApartments, "heating")
    
    assert listOfApartments == [
        {"Apartment number": 1, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 6, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 0}
        ]
    
def test_filterValue():
    listOfApartments = [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 200, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 50, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 55, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
    
    filterValue(listOfApartments, 50)

    assert listOfApartments == [
        {"Apartment number": 1, "water": 20, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 2, "water": 0, "heating": 30, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 3, "water": 0, "heating": 0, "electricity": 40, "gas": 0, "other": 0},
        {"Apartment number": 4, "water": 42, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 5, "water": 0, "heating": 0, "electricity": 20, "gas": 0, "other": 45},
        {"Apartment number": 6, "water": 25, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 7, "water": 0, "heating": 35, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 8, "water": 0, "heating": 0, "electricity": 0, "gas": 0, "other": 0},
        {"Apartment number": 9, "water": 30, "heating": 0, "electricity": 0, "gas": 15, "other": 0},
        {"Apartment number": 10, "water": 0, "heating": 33, "electricity": 0, "gas": 0, "other": 12}
        ]
