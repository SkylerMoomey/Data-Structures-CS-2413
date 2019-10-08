// Signature must be retained. Implementation must be added.

#ifndef SORT_H
#define SORT_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"
#include "DrillingRecord.h"

template <typename T>
class Sorter {
private:
	// additional member functions (methods) and variables (fields) may be added
	static unsigned long partition(ResizableArray<T>& array, const Comparator<T>& comparator, unsigned long low, unsigned long high);
	static void swap(ResizableArray<T>& array, unsigned long first, unsigned long second);
	static void quicksort(ResizableArray<T>& array, const Comparator<T>& comparator, unsigned long low, unsigned long high);

public:
	static void sort(ResizableArray<T>& array, const Comparator<T>& comparator);
};

//this will be quick sort
template <typename T>
void Sorter<T>::sort(ResizableArray<T>& array, const Comparator<T>& comparator)
{
	quicksort(array, comparator, 0, array.getSize() - 1);
}

template <typename T>
void Sorter<T>::quicksort(ResizableArray<T>& array, const Comparator<T>& comparator, unsigned long low, unsigned long high)
{
	unsigned long mid = 0;

	if (low >= high) {
		return;
	}

	mid = partition(array, comparator, low, high);


	quicksort(array, comparator, low, mid);
	quicksort(array, comparator, mid + 1, high);
}
template <typename T>
unsigned long Sorter<T>::partition(ResizableArray<T>& array, const Comparator<T>& comparator, unsigned long low, unsigned long high)
{
	unsigned long midPivotPoint = low + (high - low) / 2;
	T midPivot = array[midPivotPoint];

	unsigned long i = low;
	unsigned long k = high;

	bool finished = false;

	while (!finished)
	{
		//until array[low] is higher than array[pivot], increment low
		while (comparator.compare(array[i], midPivot) == -1)
		{
			++i; 
		}

		//until array[high] is less than array[pivot], decrement high
		while (comparator.compare(array[k], midPivot) == 1)
		{
			--k;
		}

		//if low still less than high, but array[low] > pivot and array[high] < pivot, swap them
		//after increment low, decrement high, continue loop
		if (i >= k)
		{
			finished = true;
		}
		else
		{
			swap(array, i, k);
			++i;
			--k;
		}
	}

	return k;
}

template <typename T>
void Sorter<T>::swap(ResizableArray<T>& array, unsigned long first, unsigned long second)
{
	T temp = array.get(first);

	array.replaceAt(array.get(second), first);
	array.replaceAt(temp, second);

	//swap two elements
}

#endif