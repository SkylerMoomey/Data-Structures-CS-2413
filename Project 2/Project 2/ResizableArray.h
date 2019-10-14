#ifndef RESIZABLE_ARRAY_H
#define RESIZABLE_ARRAY_H

#include "Exceptions.h"

const unsigned long DEFAULT_ARRAY_CAPACITY = 10;        // capacity used in no arg constructor

template <typename T>
class ResizableArray {
private:
    unsigned long capacity = DEFAULT_ARRAY_CAPACITY;    // maximum capacity, in items
    unsigned long size = 0;                             // actual number of items currently in array
    T* data = NULL;                                     // pointer to array of any type
    void doubleCapacity();                              // method to double array capacity
    void halveCapacity();                               // method to halve array capacity
public:
    ResizableArray();                                   // constructs array with default capacity
    ResizableArray(unsigned long capacity);             // constructs array with specified capacity
    virtual ~ResizableArray();                          // frees array space as object is deleted
    void add(T item);                                   // adds item, increments size, doubles capacity as necessary
    void addAt(T item, unsigned long index);            // adds item at index, shifts following, doubles capacity as necessary
    void replaceAt(T item, unsigned long index);        // replaces item at index, otherwise unchanged
    void removeAt(unsigned long index);                 // removes item at index, shifts following back
    T get(unsigned long index) const;                   // returns (copy of) item at index
    unsigned long getSize() const;                      // returns number of items currently in array
    unsigned long getCapacity() const;                  // returns the current capacity of the array
    T operator[](unsigned long index) const;            // returns (copy of) item at index
    void clear();                                       // removes all items from array, resets to default capacity, set size to 0
};
// Add your implementation below this line. Do not add or modify anything above this line.

//private doubleCapacity helper method
template <typename T>
void ResizableArray<T>::doubleCapacity()
{
	T* newData = new T[2 * capacity];

	for (unsigned long i = 0; i < capacity; ++i)
	{
		newData[i] = this->data[i];
	}

	this->capacity *= 2;

	delete[] this->data;
	this->data = newData;
}

//private halveCapacity helper method
template <typename T>
void ResizableArray<T>::halveCapacity()
{
	this->capacity /= 2;
	T* newData = new T[capacity];

	for (unsigned long i = 0; i < capacity; ++i)
	{
		newData[i] = this->data[i];
	}

	delete[] this->data;
	this->data = newData;
}
//default ResizableArray constructor override
template <typename T>
ResizableArray<T>::ResizableArray()
{
	data = new T[capacity];
}

//constructor that specifies ResizableArray capacity with parameter unsigned long capacity
template <typename T>
ResizableArray<T>::ResizableArray(unsigned long capacity)
{
	this->capacity = capacity;
	data = new T[this->capacity];
}

//destructor, deallocates memory for ResizableArray->data
template <typename T>
ResizableArray<T>::~ResizableArray()
{
	delete[] this->data;
}

//checks that capacity can hold another entry, then adds it, dynamically doubles array capacity if capacity already met
template <typename T>
void ResizableArray<T>::add(T item)
{
	if (size == capacity)
	{
		this->doubleCapacity();
	}

	this->data[size] = item;
	size++;
}

//checks that capacity can hold another entry, then adds it at the specified index, doubles capacity if capacity already met
template <typename T>
void ResizableArray<T>::addAt(T item, unsigned long index)
{
	//error handling block
	if (index < 0 || index > size)
	{
		throw new ExceptionIndexOutOfRange();
	}

	if (size == capacity)
	{
		this->doubleCapacity();
	}

	//check if index less than size, shift elements
	if (index < size)
	{
		for (unsigned long i = this->size - 1; i >= index; i--)
		{
			this->data[i + 1] = data[i];
		}
	}

	this->data[index] = item;
	size++;
}

//replace at method, replaces item at given index
template <typename T>
void ResizableArray<T>::replaceAt(T item, unsigned long index)
{
	//error handling
	if (index < 0 || index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}

	this->data[index] = item;
}

//removeAt method, removes item and shifts following back
template <typename T>
void ResizableArray<T>::removeAt(unsigned long index)
{
	//check for valid index
	if (index < 0 || index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}

	//move everything one down, overwriting data[index]
	for (unsigned long i = index + 1; i < size; ++i)
	{
		data[i - 1] = data[i];
	}

	size--; //decrement size

	//check if array needs to be sized down after removal of an element
	if (size <= capacity / 2)
	{
		this->halveCapacity();
	}

}

//returns T item at index
template <typename T>
T ResizableArray<T>::get(unsigned long index) const
{
	//check index within array bounds
	if (index < 0 || index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}

	return this->data[index];
}

//returns T at ResizableArray[T]
template <typename T>
T ResizableArray<T>::operator[](unsigned long index) const
{
	if (index < 0 || index >= size)
	{
		throw new ExceptionIndexOutOfRange();
	}

	return this->data[index];
}

//returns size of ResizableArray
template <typename T>
unsigned long ResizableArray<T>::getSize() const
{
	return this->size;
}

//returns capacity of ResizableArray
template <typename T>
unsigned long ResizableArray<T>::getCapacity() const
{
	return this->capacity;
}

#endif
