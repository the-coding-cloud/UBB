#include "Matrix.h"
#include <iostream>
#include <stdlib.h>
#include <exception>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols)
// theta(nrCols)
{
	if (nrLines <= 0 || nrCols <= 0)
		throw std::exception();
	this->numberOfLines = nrLines;
	this->numberOfColumns = nrCols;

	for (int i = 0; i <= nrCols; i++)
		this->columnsArray.addElement(0);

}

int Matrix::nrLines() const
// theta(1)
{
	return numberOfLines;
}

int Matrix::nrColumns() const
// theta(1)
{
	return numberOfColumns;
}

TElem Matrix::element(int i, int j) const
// O(i)
{
	if (i < 0 || i >= numberOfLines || j < 0 || j >= numberOfColumns)
		throw std::exception();

	else
		for (int index = columnsArray.elements[j]; index < columnsArray.elements[j+1]; index++)
			if (this->linesArray.elements[index] == i)
				return this->valuesArray.elements[index];

	return 0;
}

TElem Matrix::modify(int i, int j, TElem e)
// O(n)
{
	if (i < 0 || i >= numberOfLines || j < 0 || j >= numberOfColumns)
		throw std::exception();

	if (this->columnsArray.elements[j+1] - this->columnsArray.elements[j] == 0)
		//insert new position & increase index in linesArray
	{
		for (int index = j+1; index <= numberOfColumns; index++)
			this->columnsArray.elements[index] += 1;

		this->linesArray.insertElement(i, this->columnsArray.elements[j]);
		this->valuesArray.insertElement(e, this->columnsArray.elements[j]);
		return 0;

	}

	else
	{
		int insertIndex;
		for (int index = columnsArray.elements[j]; index < columnsArray.elements[j+1]; index++)
		{
			if (this->linesArray.elements[index] == i)
				//we modify if e != 0
				if (e != 0)
				{
					TElem oldValue = this->valuesArray.elements[index];
					this->valuesArray.elements[index] = e;
					return oldValue;
				}

				//we delete if e == 0
				else
				{
					TElem oldValue = this->valuesArray.elements[index];
					this->columnsArray.deleteElement(index);
					this->valuesArray.deleteElement(index);
					return oldValue;
				}

			if (this->linesArray.elements[index] < i)
				insertIndex = index;
		}
		//insert new position & increase index in linesArray

		for (int index = j+1; index <= numberOfColumns; index++)
			this->columnsArray.elements[index]++;
		this->linesArray.insertElement(i, insertIndex);
		this->valuesArray.insertElement(e, insertIndex);
		return 0;
	}
	throw std::exception();
}

void Matrix::printMatrix() const
// needed it for testing
{
	columnsArray.printArray();
	linesArray.printArray();
	valuesArray.printArray();
}