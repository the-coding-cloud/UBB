class Bag:

    # creates a new, empty Bag
    def __init__(self):
        self.elements = []
        self.frequency = []

    # adds a new element to the Bag
    def add(self, e):
        if e not in self.elements:
            self.elements.append(e)
            self.frequency.append(1)
            
        else:
            for index in range (0, len(self.elements)):
                if self.elements[index] == e:
                    self.frequency[index] += 1
                    return

    # removes one occurrence of an element from a Bag
    # returns True if an element was actually removed (the Bag contained the element e), or False if nothing was removed
    def remove(self, e):
        if e in self.elements:
            for index in range (0, len(self.elements)):
                if self.elements[index] == e:
                    if self.frequency[index] >= 2:
                        self.frequency[index] -= 1
                        return True
                    else:
                        self.elements.pop(index)
                        self.frequency.pop(index)
                        return True
        else:
            return False

    # searches for an element e in the Bag
    # returns True if the Bag contains the element, False otherwise
    def search(self, e):
        if e in self.elements:
            return True
        else:
            return False

    # counts and returns the number of times the element e appears in the bag
    def nrOccurrences(self, e):
        for index in range (0, len(self.elements)):
                if self.elements[index] == e:
                    return self.frequency[index]
                
        return 0

    # returns the size of the Bag (the number of elements)
    def size(self):
        size = 0
        for index in range (0, len(self.elements)):
            size = size + self.frequency[index]
            
        return size

    # returns True if the Bag is empty, False otherwise
    def isEmpty(self):
        if len(self.elements) == 0:
            return True
        else:
            return False

    # returns a BagIterator for the Bag
    def iterator(self):
        return BagIterator(self)


class BagIterator:

    #creates an iterator for the Bag b, set to the first element of the bag, or invalid if the Bag is empty
    def __init__(self, b):
        self.position = 0
        self.frequency = 1
        self.bag = b

    # returns True if the iterator is valid
    def valid(self):
        if self.position < len(self.bag.elements) and self.frequency <= self.bag.frequency[position]:
            return True
        else:
            return False

    # returns the current element from the iterator.
    # throws ValueError if the iterator is not valid
    def getCurrent(self):
        if self.valid():
            return self.bag.elements[self.position]
        else:
            raise ValueError

    # moves the iterator to the next element
    #throws ValueError if the iterator is not valid
    def next(self):
        if self.valid():
            if self.frequency == self.bag.frequency(self.position):
                self.position += 1
                self.frequency = 1
            else:
                self.frequency += 1
        else:
            raise ValueError

    # sets the iterator to the first element from the Bag
    def first(self):
        self.position = 0
        self.frequency = 1
