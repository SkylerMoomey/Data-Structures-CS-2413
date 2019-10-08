// Signature must be retained. Implementation must be added.

#ifndef SEARCH_H
#define SEARCH_H

#include "Exceptions.h"
#include "ResizableArray.h"
#include "Comparator.h"

// returns FIRST array location matching the given item (based on the comparator)
// if not found, returns -(location to insert + 1)
template <typename T>
long long binarySearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator) 
{
	
	unsigned long low = 0;
	unsigned long mid = 0;
	unsigned long high = array.getSize() - 1;

	while (high >= low)
	{
		mid = (high + low) / 2;

		if (comparator.compare(array[mid], item) == -1)
		{
			low = mid + 1;
		}
		else if (comparator.compare(array[mid], item) == 1)
		{
			high = mid;
		}
		else
		{
			while (mid > 0 && comparator.compare(array[mid - 1], item) == 0)
			{
				mid--;
			}

			return mid;
		}
	}

	//if item < array[mid], return -(mid - 1 + 1) i.e. -mid
	if (comparator.compare(item, array[mid]) == -1)
	{
		return -(long)mid;
	}

	//if item > array[mid], return -(mid + 1 + 1) i.e. -(mid + 2)| ex: mid == 5, insertion point = 6, return -7
	else
	{
		return -(long)(mid + 2);
	}
}

template <typename T>
long long linearSearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator)
{
	for (unsigned int i = 0; i < array.getSize(); ++i)
	{
		if (comparator.compare(array.get(i), item) == 0)
		{
			return i;
		}
	}

	return -1;
}

template <typename T>
long long linearSearch(const T& item, const ResizableArray<T>& array, const Comparator<T>& comparator, long firstIndex)
{

	for (unsigned int i = (int)firstIndex; i < array.getSize(); ++i)
	{
		if (comparator.compare(array.get(i), item) == 0)
		{
			return i;
		}
	}

	return -1;
}
#endif