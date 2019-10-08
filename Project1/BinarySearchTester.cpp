#include <iostream>
#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "Search.h"
#include "DrillingRecordComparator.h"
#include "Sorter.h"

bool assert(long long actualIndex, long long expectedIndex, int column)
{
	if (actualIndex != expectedIndex)
	{
		std::cout << "binary search failed on column " << column << "||expected index: " << expectedIndex << ", actual index: " << actualIndex << std::endl;
		return false;
	}

	std::cout << "successful binary search on column " << column << "||expected index: " << expectedIndex << " == actual index: " << actualIndex << std::endl;
	return true;
}

void binarySearchTester();

int main()
{
	binarySearchTester();
	return 0;
}

void binarySearchTester()
{
	ResizableArray<DrillingRecord> arr(4);

	DrillingRecord r1;
	DrillingRecord r2;
	DrillingRecord r3;
	DrillingRecord r4;

	r1.setString("b", 0);
	r2.setString("d", 0);
	r3.setString("a", 0);
	r4.setString("c", 0);
	r1.setNum(2.0, 0);
	r2.setNum(4.0, 0);
	r3.setNum(1.0, 0);
	r4.setNum(3.0, 0);

	arr.add(r1);
	arr.add(r2);
	arr.add(r3);
	arr.add(r4);


	//sort on doubles in column 2
	DrillingRecordComparator compDouble(2);
	Sorter<DrillingRecord>::sort(arr, compDouble);
	//search for item on column 2

	DrillingRecord search1;
	search1.setNum(3.0, 0);
	long long actualIndex = binarySearch(search1, arr, compDouble);
	long long expectedIndex = 2;

	assert(expectedIndex, actualIndex, 2);
	

	//sort on strings
	DrillingRecordComparator compString(0);
	Sorter<DrillingRecord>::sort(arr, compString);

	DrillingRecord search2;
	search2.setString("d", 0);
	actualIndex = binarySearch(search2, arr, compDouble);
	expectedIndex = 3;

	assert(expectedIndex, actualIndex, 0);

}