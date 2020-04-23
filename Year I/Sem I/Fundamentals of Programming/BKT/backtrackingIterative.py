def candidateFound(candidate):
    toPrint = ""
    for element in candidate:
        if element == 0:
            toPrint += "("
        else:
            toPrint += ")"
        
    print (toPrint)

def isSolution(candidate, length):
    if len (candidate) == length:
        return True
    
    return False

def consistent(candidate):
    closedParentheses = 0
    openParentheses = 0
    pairs = 0
    
    for element in candidate:
        if element == 0:
            openParentheses += 1
            pairs += 1
            
        else:
            closedParentheses +=1
            pairs -=1
            
    if 2 in candidate:
        return False
            
    if len(candidate) > length:
        return False
            
    if pairs < 0:
        return False
    
    if len(candidate) == length and closedParentheses != openParentheses:
        return False
    
    else:
        return True

def backtrackingIterative(length):

    candidate = [-1]
    while len(candidate) > 0:
        chosen = False
        while not chosen and candidate[len(candidate) - 1] < 2:
            candidate[len(candidate) - 1] += 1
            chosen = consistent(candidate)
        if chosen:
            if isSolution(candidate, length):
                candidateFound(candidate)
            else:
                candidate.append(-1)
        else:
            candidate = candidate[:-1]
       
       
            
while True:
    length = int(input('Enter the number of parentheses: '))
    if length > 0 and length % 2 == 0:
        break
    else:
        continue

backtrackingIterative(length)