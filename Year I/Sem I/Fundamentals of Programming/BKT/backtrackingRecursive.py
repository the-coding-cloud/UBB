def solutionFound(candidate):
    toPrint = ""
    for element in candidate:
        toPrint += element
        
    print (toPrint)

def solution(candidate):
    if len (candidate) == length:
        return True
    
    return False

def consistent(candidate):
    closedParantheses = 0
    openParantheses = 0
    pairs = 0
    
    for element in candidate:
        if element == "(":
            openParantheses += 1
            pairs += 1
            
        else:
            closedParantheses +=1
            pairs -=1
            
    if len(candidate) > length:
        return False
            
    if pairs < 0:
        return False
    
    if len(candidate) == length and closedParantheses != openParantheses:
        return False
    
    else:
        return True
    

def backtrackingRecursive(candidate):
    candidate.append(0) #add a new component to the candidate solution
    for element in ["(", ")"]:
        candidate[-1] = element #set current component
        if consistent(candidate):
            if solution(candidate):
                solutionFound(candidate)
            backtrackingRecursive(candidate) #recursive invocation to deal with necandidatet components
    candidate.pop()
   
    
    

while True:
    length = int(input('Enter the number of parentheses: '))
    if length > 0 and length % 2 == 0:
        break
    else:
        continue

backtrackingRecursive([])
