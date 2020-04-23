#pragma once

template <typename ElementType>
class DynamicVector
{
private:
	ElementType* elements;
	int size;
	int capacity;

public:
	DynamicVector(int capacity = 100);

	DynamicVector(const DynamicVector& vector);

	~DynamicVector();

	ElementType& operator[](unsigned int position);

	void addElement(const ElementType& newElement);

	void deleteElement(const ElementType& elementToDelete);

	int searchElement(const ElementType& elementToSearch);

	int getSize() const;

private:
	void resize(double factor = 2);

};

template <typename ElementType>
DynamicVector<ElementType>::DynamicVector(int capacity)
{
	this->size = 0;
	this->capacity = capacity;
	this->elements = new ElementType[capacity];
}


template <typename ElementType>
DynamicVector<ElementType>::DynamicVector(const DynamicVector<ElementType>& vector)
{
	this->size = vector.size;
	this->capacity = vector.capacity;
	this->elements = new ElementType[this->capacity];
	for (int i = 0; i < this->size; i++)
		this->elements[i] = vector.elements[i];
}


template <typename ElementType>
DynamicVector<ElementType>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename ElementType>
ElementType& DynamicVector<ElementType>::operator[](unsigned int position)
{
	return this->elements[position];
}

template <typename ElementType>
void DynamicVector<ElementType>::addElement(const ElementType& newElement)
{
	if (this->size == this->capacity)
		this->resize();

	this->elements[this->size] = newElement;
	this->size++;
}

template <typename ElementType>
void DynamicVector<ElementType>::deleteElement(const ElementType& elementToDelete)
{
	int deleteIndex = 0;
	for (int index = 0; index <= this->size; index++)
		if (this->elements[index] == elementToDelete)
		{
			deleteIndex = index;
			break;
		}

	for (int index = deleteIndex; index <= this->size; index++)
		this->elements[index] = this->elements[index + 1];

	this->size--;
}

template <typename ElementType>
int DynamicVector<ElementType>::searchElement(const ElementType& elementToSearch)
{
	for (int index = 0; index <= this->size; index++)
		if (this->elements[index] == elementToSearch)
			return index;

	return -1;

}

template <typename ElementType>
void DynamicVector<ElementType>::resize(double factor)
{
	this->capacity *= static_cast<int>(factor);

	ElementType* newElements = new ElementType[this->capacity];
	for (int index = 0; index < this->size; index++)
		newElements[index] = this->elements[index];

	delete[] this->elements;
	this->elements = newElements;
}

template <typename ElementType>
int DynamicVector<ElementType>::getSize() const
{
	return this->size;
}
