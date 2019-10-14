#include <iostream>
#include <iomanip>
#include "DrillingRecord.h"


//default constructor for a DrillingRecord
DrillingRecord::DrillingRecord()
{
	for (unsigned int i = 0; i < MAX_NUMS; ++i)
	{
		this->nums[i] = 0.0;
	}

	for (unsigned int j = 0; j < MAX_STRINGS; ++j)
	{
		this->strings[j] = "";
	}

}
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
	//space check
	if (numCtr >= MAX_NUMS)
	{
		throw new ExceptionIndexOutOfRange;
	}

	this->nums[numCtr] = num;

	this->numCtr++;
}
//method to add a string value to DrillingRecord
void DrillingRecord::addString(std::string string)
{
	//space check
	if (strCtr >= MAX_STRINGS)
	{
		throw new ExceptionIndexOutOfRange;
	}

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

//sets index value, throws exception if index >= max_nums
void DrillingRecord::setNum(double num, unsigned int index)
{
	if (index >= MAX_NUMS)
	{
		throw new ExceptionIndexOutOfRange;
	}

	this->nums[index] = num;
}

//sets index value, throws exception if index >= max_strings
void DrillingRecord::setString(std::string string, unsigned int index)
{
	if (index >= MAX_STRINGS)
	{
		throw new ExceptionIndexOutOfRange;
	}

	this->strings[index] = string;
}