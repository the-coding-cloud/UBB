#include "Matrix.h"
#include <iostream>
#include <stdlib.h>
#include <exception>

using namespace std;

Matrix::Matrix(int nrLines, int nrCols)
{
	if (nrLines <= 0 || nrCols <= 0)
		throw std::exception();
	this->numberOfLines = nrLines;
	this->numberOfColumns = nrCols;

	for (int i = 0; i <= nrCols; i++)
		this->columnsArray.addElement(0);

}

int Matrix::nrLines() const
{
	return numberOfLines;
}

int Matrix::nrColumns() const
{
	return numberOfColumns;
}

TElem Matrix::element(int i, int j) const
{
	if (i <= 0 || i > numberOfLines || j <= 0 || j > numberOfColumns)
		throw std::exception();

	else
		for (int index = columnsArray.elements[j - 1]; index < columnsArray.elements[j]; index++)
			if (this->linesArray.elements[index] == i)
				return this->valuesArray.elements[index];

	return 0;
}

TElem Matrix::modify(int i, int j, TElem e)
{
	if (i <= 0 || i >= numberOfLines || j <= 0 || j >= numberOfColumns)
		throw std::exception();

	if (this->columnsArray.elements[j] - this->columnsArray.elements[j - 1] == 0)
		//insert new position & increase index in linesArray
	{
		for (int index = j; index <= numberOfColumns; index++)
			this->columnsArray.elements[index] += 1;

		this->linesArray.insertElement(i, this->columnsArray.elements[j-1]);
		this->valuesArray.insertElement(e, this->columnsArray.elements[j-1]);
		return 0;

	}

	else
	{
		int insertIndex;
		for (int index = columnsArray.elements[j - 1]; index < columnsArray.elements[j]; index++)
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

		for (int index = j; index <= numberOfColumns; index++)
			this->columnsArray.elements[index]++;
		this->linesArray.insertElement(i, insertIndex);
		this->valuesArray.insertElement(e, insertIndex);
		return 0;
	}
	throw std::exception();
}

void Matrix::printMatrix() const
{
	columnsArray.printArray();
	linesArray.printArray();
	valuesArray.printArray();
}