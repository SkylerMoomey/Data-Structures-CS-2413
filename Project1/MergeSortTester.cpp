#include "DrillingRecord.h"
#include "ResizableArray.h"
#include "DrillingRecordComparator.h"
#include <iostream>
#include "Sorter.h"


//assert method
template <typename T>
bool assert(T expected, T actual, unsigned long column)
{
	if (expected != actual)
	{
		std::cout << "merge sort failed on column " << column << "||expected: " << expected << ", actual: " << actual << std::endl;
		return false;
	}

	std::cout << "successful merge sort on column " << column << "||expected: " <<expected <<  " == actual: " << actual << std::endl;
	return true;
}

//test methods
void mergeSortTest(); //tests merge part of merge sort


int main()
{
	mergeSortTest();
	return 0;
}

void mergeSortTest()
{
	ResizableArray<DrillingRecord> arr(4);
	Sorter<DrillingRecord> sorter;

	DrillingRecord r1;
	DrillingRecord r2;
	DrillingRecord r3;
	DrillingRecord r4;
	DrillingRecord r5;
	DrillingRecord r6;
	DrillingRecord r7;
	DrillingRecord r8;

	r1.setString("e", 0);
	r2.setString("h", 0);
	r3.setString("g", 0);
	r4.setString("f", 0);
	r5.setString("a", 0);
	r6.setString("d", 0);
	r7.setString("b", 0);
	r8.setString("c", 0);

	r1.setNum(2.0, 0);
	r2.setNum(4.0, 0);
	r3.setNum(1.0, 0);
	r4.setNum(3.0, 0);
	r5.setNum(0.0, 0);
	r6.setNum(0.0, 0);
	r7.setNum(0.0, 0);
	r8.setNum(0.0, 0);

	arr.add(r1);
	arr.add(r2);
	arr.add(r3);
	arr.add(r4);
	arr.add(r5);
	arr.add(r6);
	arr.add(r7);
	arr.add(r8);


	//sort on doubles in column 2
	DrillingRecordComparator compDouble(2);
	Sorter<DrillingRecord>::sort(arr, compDouble);

	double actualR1 = arr.get(0).getNum(0);
	double expectedR1 = 1.0;

	assert(actualR1, expectedR1, 2);

	double actualR2 = arr.get(1).getNum(0);
	double expectedR2 = 2.0;

	assert(actualR2, expectedR2, 2);

	double actualR3 = arr.get(2).getNum(0);
	double expectedR3 = 3.0;

	assert(actualR3, expectedR3, 2);

	double actualR4 = arr.get(3).getNum(0);
	double expectedR4 = 4.0;

	assert(actualR4, expectedR4, 2);

	//sort on strings
	DrillingRecordComparator compString(0);
	Sorter<DrillingRecord>::sort(arr, compString);

	std::string actualR1Date = arr.get(0).getString(0);
	std::string expectedR1Date = "a";

	assert(actualR1Date, expectedR1Date, 0);

	std::string actualR2Date = arr.get(1).getString(0);
	std::string expectedR2Date = "b";

	assert(actualR2Date, expectedR2Date, 0);

	std::string actualR3Date = arr.get(2).getString(0);
	std::string expectedR3Date = "c";

	assert(actualR3Date, expectedR3Date, 0);

	std::string actualR4Date = arr.get(3).getString(0);
	std::string expectedR4Date = "d";

	assert(actualR4Date, expectedR4Date, 0);

	std::string actualR5Date = arr.get(4).getString(0);
	std::string expectedR5Date = "e";

	assert(actualR5Date, expectedR5Date, 0);

	std::string actualR6Date = arr.get(5).getString(0);
	std::string expectedR6Date = "f";

	assert(actualR6Date, expectedR6Date, 0);

	std::string actualR7Date = arr.get(6).getString(0);
	std::string expectedR7Date = "g";

	assert(actualR7Date, expectedR7Date, 0);

	std::string actualR8Date = arr.get(7).getString(0);
	std::string expectedR8Date = "h";

	assert(actualR8Date, expectedR8Date, 0);

}