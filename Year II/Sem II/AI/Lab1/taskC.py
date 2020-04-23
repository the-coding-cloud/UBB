"""
Task C:
    Develop an application that performs random searches to the following problems. The
    applications should follow the following conditions:
            - a menu to choose the number of the problem
            - allows to choose the maximum number of attempts to find a solution
            - prints the found solution
"""

from numpy import random
from copy import deepcopy
import math


### SUDOKU

class SudokuPuzzle:
    def __init__(self, n, table):
        self.n = n
        self.table = table

    def generateRandomSolution(self):
        solution = deepcopy(self.table)

        # Here we count how many values from the sudoku table are already fixed
        count = 0
        for i in range(0, self.n):
            for j in range(0, self.n):
                if solution[i][j] != 0:
                    count += 1

        # We generate then n^2-count random numbers in order to fill in the empty spaces
        size = self.n * self.n - count
        randomNumbers = random.randint(1, self.n + 1, size)
        index = 0

        for i in range(0, self.n):
            for j in range(0, self.n):
                if solution[i][j] == 0:
                    solution[i][j] = randomNumbers[index]
                    index += 1

        return solution

    def isSolution(self, solution):
        # Check lines
        for i in range(0, self.n):
            if len(solution[i]) > len(set(solution[i])):
                return False

        # Check columns
        for j in range(0, self.n):
            column = []
            for i in range(0, self.n):
                column.append(solution[i][j])
            if len(column) > len(set(column)):
                return False

        # Check squares
        miniSquareSize = int(math.sqrt(self.n))
        for startLineSquare in range(0, self.n, miniSquareSize):
            for startColumnSquare in range(0, self.n, miniSquareSize):
                values = []
                for i in range(startLineSquare, startLineSquare + miniSquareSize):
                    for j in range(startColumnSquare, startColumnSquare + miniSquareSize):
                        values.append(solution[i][j])

                if len(values) > len(set(values)):
                    return False

        return True

    def playGame(self, numberOfTrials):
        print("Start game")
        for i in range(0, numberOfTrials):
            solution = self.generateRandomSolution()
            if i % 1000 == 0:
                print(i)
            if self.isSolution(solution):
                print("Found solution:")
                print(i)
                print(solution)
                return

        print("No solutions were found")


def readSudoku():
    """
    Reads a line that contains n, an integer representing the size of the table,
    then n lines containing the values from the sudoku table (0 means empty square)
    """
    with open("input.txt", "r") as file:
        n = int(file.readline().strip())
        matrix = []
        for i in range(n):
            line = file.readline().strip().split(" ")

            for j in range(n):
                line[j] = int(line[j])

            matrix.append(line)

    return [n, matrix]


### CRYPTARIHTMETIC GAME

class LetterPuzzle:
    def __init__(self, words, result, operation):
        self.words = words
        self.result = result
        self.operation = operation

    def generateRandomSolution(self):
        solution = {}
        letters = []
        solutionWords = []

        # Collect all the letters from the words
        for word in self.words:
            for i in range(0, len(word)):
                letters.append(word[i])

        for i in range(0, len(self.result)):
            letters.append(self.result[i])

        # Assign numbers to letters
        letters = set(letters)
        for letter in letters:
            solution[letter] = random.randint(0, 16, 1)[0]

        # Convert each word to its "digit" form (list of digits) for easier checking afterwards
        solutionWord = []
        for word in self.words:
            for i in range(0, len(word)):
                solutionWord.append(solution[word[i]])

            solutionWords.append(solutionWord)
            solutionWord = []

        solutionResult = []
        for i in range(0, len(self.result)):
            solutionResult.append(solution[self.result[i]])

        return [solutionWords, solutionResult, solution]

    def isSolution(self, solution):
        solutionWords = solution[0]
        solutionResult = solution[1]
        solutionKey = solution[2]

        # Checks if words start with 0
        firstLetters = []
        for word in self.words:
            if word[0] not in firstLetters:
                firstLetters.append(word[0])

        for letter in firstLetters:
            if solutionKey[letter] == 0:
                return False

        # Checks if each letter is assigned a distinct value
        values = solutionKey.values()
        if len(values) > len(set(values)):
            return False

        # Checks the sum
        operationTerms = []
        for word in solutionWords:
            word.reverse()
            number = 0
            power = 1
            for num in word:
                number += num * power
                power *= 16

            operationTerms.append(number)

        solutionResult.reverse()
        result = 0
        power = 1
        for num in solutionResult:
            result += num * power
            power *= 16

        if self.operation == 1:
            s = 0
            for term in operationTerms:
                s += term

        if self.operation == 2:
            s = operationTerms[0]
            for term in operationTerms[1:]:
                s -= term

        if s == result:
            return True

        return False

    def playGame(self, numberOfTrials):
        print("Start game")
        for i in range(0, numberOfTrials):
            solution = self.generateRandomSolution()
            if i % 10000 == 0:
                print(i)
            if self.isSolution(solution):
                print("Found solution:")
                print(i)
                print(solution[2])
                return

        print("No solutions were found")


def readLetterGame():
    """
    Reads games like: "send + more = money" or "never - drive = ride"
    """
    with open("input.txt", "r") as file:
        line = file.readline().strip().split(" ")

        op = line[1]
        if op == "+":
            operator = 1
        else:
            operator = 2

        words = []
        for elem in line:
            if elem == "=":
                break
            elif (elem != '+') and (elem != "-"):
                words.append(elem)

        result = line[len(line)-1]

    return [words, result, operator]


### BOARD GAME

class BoardPuzzle:
    def __init__(self):
        self.rows = 5
        self.columns = 6
        self.pieces = [[(0, 1), (0, 1), (0, 1)],  # line
                       [(1, 0), (0, 1), (0, 1), (-1, 0)],  # U
                       [(0, 1), (1, 0), (-1, 1)],  # T
                       [(1, 0), (0, 1), (0, 1)],  # L down
                       [(0, 1), (0, 1), (1, 0)]]  # L up

    def generateRandomSolution(self):
        table = [[0 for col in range(self.columns)] for row in range(self.rows)]

        # The idea is to randomly generate coordinates for the "origin" of each piece
        for piece in range(0, len(self.pieces)):
            row = random.randint(0, self.rows, 1)[0]
            col = random.randint(0, self.columns, 1)[0]

            i = 0

            table[row][col] = piece + 1  # Marking the initial square

            while i < len(self.pieces[piece]):
                row += self.pieces[piece][i][0]
                col += self.pieces[piece][i][1]

                if row >= self.rows or col >= self.columns:  # Stopping condition (exceeds the board) so that the app hopefully doesn't crash
                    break

                table[row][col] = piece + 1  # Construct the piece by modifying the coordinates for the next squares of the piece (above)
                i += 1

        return table

    def isSolution(self, solution):
        zeroes = 0
        # If the pieces overlap or they aren't properly placed on the table, the amount of empty squares is greater than 9
        # Otherwise, it is exactly 9 for this game
        for i in range(0, self.rows):
            for j in range(0, self.columns):
                if solution[i][j] == 0:
                    zeroes += 1

        if zeroes == 9:
            return True

        return False

    @staticmethod
    def printBoard(board):
        s = ""
        for row in board:
            for piece in row:
                s += str(piece) + " "
            s += "\n"
        print(s)

    def playGame(self, numberOfTrials):
        print("Start game")
        for i in range(0, numberOfTrials):
            solution = self.generateRandomSolution()
            if i % 10000 == 0:
                print(i)
            if self.isSolution(solution):
                print("Found solution:")
                print(i)
                self.printBoard(solution)
                return

        print("No solutions were found")


def printMenu():
    print("Menu:")
    print("1. Play Sudoku")
    print("2. Play the Cryptarithmetic Game")
    print("3. Play the Tetris wannabe")


def playSudoku():
    print("Choose a game:")
    print("1. 3 - - 2\n   - 1 4 -\n   1 2 - 4\n   - 3 2 1")
    print(
        '2. - 2 - 6 - 8 - - 5\n   5 8 - - - 9 7 - -\n   - - 7 - 4 - - 2 8\n   3 7 - 4 - 1 5 - -\n   6 - - - 8 - - - 5\n   - - 8 - - 2 - 1 3\n   8 - 6 - 2 - 1 - -\n   - - 9 8 - - - 3 6\n   7 - - 3 - 6 - 9 -')
    print("3. Read game from file")

    game = input().strip()

    if game == "1":
        puzzle = SudokuPuzzle(4, [[3, 0, 0, 2], [0, 1, 4, 0], [1, 2, 0, 4], [0, 3, 2, 1]])
    elif game == "2":
        puzzle = SudokuPuzzle(9, [[0, 2, 0, 6, 0, 8, 0, 0, 5], [5, 8, 0, 0, 0, 9, 7, 0, 0], [0, 0, 7, 0, 4, 0, 0, 2, 8],
                                  [3, 7, 0, 4, 0, 1, 5, 0, 0], [6, 0, 0, 0, 8, 0, 0, 0, 5], [0, 0, 8, 0, 0, 2, 0, 1, 3],
                                  [8, 0, 6, 0, 2, 0, 1, 0, 0], [0, 0, 9, 8, 0, 0, 0, 3, 6], [7, 0, 0, 3, 0, 6, 0, 9, 0]])
    elif game == "3":
        n, matrix = readSudoku()
        print(n)
        print(matrix)
        puzzle = SudokuPuzzle(n, matrix)
    else:
        print("Invalid choice, sorry")
        return

    numberOfTrials = int(input("Number of trials: ").strip())
    puzzle.playGame(numberOfTrials)


def playLetterGame():
    print("Choose a game:")
    print("1. I + AM = ME")
    print("2. SEND + MORE = MONEY")
    print("3. NEVER - DRIVE = RIDE")
    print("4. Read game from file")
    game = input().strip()

    if game == "1":
        puzzle = LetterPuzzle(["i", "am"], "me", 1)
    elif game == "2":
        puzzle = LetterPuzzle(["send", "more"], "money", 1)
    elif game == "3":
        puzzle = LetterPuzzle(["never", "drive"], "ride", 2)
    elif game == "4":
        words, resultWord, operator = readLetterGame()
        puzzle = LetterPuzzle(words, resultWord, operator)
    else:
        print("Invalid choice, sorry")
        return

    numberOfTrials = int(input("Number of trials: ").strip())
    puzzle.playGame(numberOfTrials)


def playTetrisWannabe():
    puzzle = BoardPuzzle()
    numberOfTrials = int(input("Number of trials: ").strip())
    puzzle.playGame(numberOfTrials)


def run():
    printMenu()
    choice = input().strip()
    if choice == "1":
        playSudoku()
    elif choice == "2":
        playLetterGame()
    elif choice == "3":
        playTetrisWannabe()
    else:
        print("wtf did you want to play")


run()
