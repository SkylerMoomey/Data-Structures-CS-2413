/*Class to represent an individual record of drilling data. Each record houses
an array of strings of length two for the date and time as well as an array of 
doubles to represent each column of numeric data*/

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
	if (this->numCtr >= 16) return;

	this->nums[numCtr] = num;

	this->numCtr++;
}
//method to add a string value to DrillingRecord
void DrillingRecord::addString(std::string string)
{
	if (this->strCtr >= 2) return;

	this->strings[strCtr] = string;

	this->strCtr++;
}

//method to get the numeric data from a specified index 
double DrillingRecord::getNum(unsigned int index)
{
	if (index < 16) 
	{
		return this->nums[index];
	}
	
	return -1;
}

//method to get the string data from a specified index (0 = date, 1 = time)
std::string DrillingRecord::getString(unsigned int index)
{
	if (index < 2)
	{
		return this->strings[index];
	}

	return "index out of bounds";
}

