#include <iostream>
#include <iomanip>
#include "DrillingRecord.h"


//overloaded output operator for DrillingRecord
std::ostream& operator<<(std::ostream& os, const DrillingRecord& record)
{
	for (unsigned int i = 0; i < record.strCtr; i++)
	{
		os << record.strings[i] << ';';
	}
	for (unsigned int j = 0; j < record.numCtr - 1; j++)
	{
		os << std::fixed << std::setprecision(2) << record.nums[j] << ';'; //make sure output is set to precision of 2 decimal places
	}

	os << record.nums[15];

	return os;
}

//method to add a floating point value to DrillingRecord
void DrillingRecord::addNum(double num)
{
	this->nums[numCtr] = num;

	this->numCtr++;
}
//method to add a string value to DrillingRecord
void DrillingRecord::addString(std::string string)
{
	this->strings[strCtr] = string;

	this->strCtr++;
}

//method to get the numeric data from a specified index 
double DrillingRecord::getNum(unsigned int index) const
{
	return this->nums[index];
}

//method to get the string data from a specified index (0 = date, 1 = time)
std::string DrillingRecord::getString(unsigned int index) const
{
	return this->strings[index];
}