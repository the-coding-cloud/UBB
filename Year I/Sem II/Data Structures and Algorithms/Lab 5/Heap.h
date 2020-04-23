#pragma once
#include <list>

using namespace std;

typedef int TElem;
typedef bool(*Relation) (TElem e1, TElem e2);
typedef list<TElem>::iterator iter;
typedef struct {
	iter current_position;
	iter end_of_list;
} my_pair;
//typedef pair<iter, iter> iter_pair;
typedef my_pair iter_pair;

class Heap
{
	Relation rel;
	iter_pair* elements;
	int size = 0;
	int lists = 0;
	int capacity = 100;
	void swap(int index1, int index2)
	{
		iter_pair aux = this->elements[index1];
		this->elements[index1] = this->elements[index2];
		this->elements[index2] = aux;
	}
	void bubble_down(int index)
	{
		int left_child = index * 2;
		int right_child = index * 2 + 1;
		int largest = index;

		if (left_child <= this->lists && this->rel(*(this->elements[left_child].current_position), *(this->elements[largest].current_position)))
			largest = left_child;
		
		if (right_child <= this->lists && this->rel(*this->elements[right_child].current_position, *this->elements[largest].current_position))
			largest = right_child;
		
		if (largest != index)
		{
			this->swap(index, largest);
			this->bubble_down(largest);
		}
	}
	void bubble_up(int index)
	{
		if (index == 1)
			return;
		if (this->rel(*(this->elements[index].current_position), *(this->elements[index / 2].current_position)))
		{
			this->swap(index, index / 2);
			this->bubble_up(index / 2);
		}
	}
	void resize()
	{
		iter_pair* new_elements = new iter_pair[this->capacity * 2];
		for (int i = 0; i < this->capacity; i++)
			new_elements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_elements;
	}
public:
	Heap()
	{

	}
	int length()
	{
		return this->size;
	}
	void insert(std::list<std::list<TElem>>::iterator l)
	{
		iter_pair new_element;
		new_element.current_position = l->begin();
		new_element.end_of_list = l->end();
		this->size += l->size();
		this->lists++;
		if (this->capacity == this->lists)
			this->resize();
		this->elements[this->lists] = new_element;
		this->bubble_up(this->lists);

	}
	TElem get_root()
	{
		if (this->size > 0)
			return *(this->elements[1].current_position);
		return -1;
	}
	TElem pop_root()
	{
		if (this->size > 0)
		{

			iter_pair aux = this->elements[1];
			this->elements[1].current_position++;
			if (this->elements[1].current_position == this->elements[1].end_of_list)
			{
				this->elements[1] = this->elements[this->lists];
				this->lists--;
			}
			this->bubble_down(1);
			this->size--;

			return *aux.current_position;
		}
		return -1;
	}
	Heap(Relation rel)
	{
		this->rel = rel;
		this->elements = new iter_pair[this->capacity];
		
	}
	~Heap()
	{
		delete[] this->elements;
	}
};

