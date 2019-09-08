/*
Class to represent a dynamically sized array of DrillingRecord objects
*/
#include "DrillingRecordArray.h"

//default constructor for DrillingRecordArray, sets capacity to ten
DrillingRecordArray::DrillingRecordArray() 
{
	this->data = new DrillingRecord[capacity];
} 

//constructor for DrillingRecordArray with initial capacity specified
DrillingRecordArray::DrillingRecordArray(unsigned int capacity)
{
	this->capacity = capacity;
	this->data = new DrillingRecord[capacity];
}

//destructor for DrillingRecordArray, deletes this-> data if not NULL
DrillingRecordArray::~DrillingRecordArray()
{
	if (this->data != NULL)
	{
		delete[] this->data;
	}
}

//method that adds a DrillingRecord to this->data of a DrillingRecordArray
void DrillingRecordArray::add(DrillingRecord record)
{
	//check to make sure capacity can fit new record
	if (this->size == this->capacity)
	{
		this->capacity = 2 * this->capacity; //double capacity

		DrillingRecord* newData = new DrillingRecord[this->capacity]; //make new array with doubled capacity
		
		for (unsigned int i = 0; i < this->size; ++i)
		{
			newData[i] = this->data[i];
		}

		delete[] this->data; // delete old array

		this->data = newData; //reassign data pointer with new doubled array
	}

	this->data[size] = record; //add new record to array
	this->size = this->size + 1; //increment size
}

//method to retrieve the DrillingRecord at a given index in this->data
DrillingRecord DrillingRecordArray::get(unsigned int index)
{
		return this->data[index];
}