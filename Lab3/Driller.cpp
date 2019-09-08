// Driller0.3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <set>
#include <sstream>
#include "DrillingRecord.h"
#include "DrillingRecordArray.h"

bool checkDate(std::string line, std::string date, int lineNumber);
bool checkTimeStamp(std::string line, std::set<std::string>& timeStamps, int lineNumber);
bool checkDoubles(std::string line, int lineNumber);
std::string getDate(std::string line);
std::string getTime(std::string line);
double* getDoubles(std::string line);
void loadData(DrillingRecordArray* arr, std::string date, std::string time, double* doubleArray);


int main()
{
	std::string line;
	std::string date;
	int lineNumber = 0;
	int size = 0;
	std::set<std::string> timeStamps;

	std::getline(std::cin, line); //read in and throw out first line

	bool firstLine = true;

	DrillingRecordArray* records = new DrillingRecordArray();

	while (std::getline(std::cin, line))
	{
		if (firstLine)
		{
			date = getDate(line);
			firstLine = false;
		}

		bool dateCheckPassed = checkDate(line, date, lineNumber);

		if (dateCheckPassed)
		{
			bool timeStampCheckPassed = checkTimeStamp(line, timeStamps, lineNumber);

			if (timeStampCheckPassed)
			{

				bool doubleCheckPassed = checkDoubles(line, lineNumber);

				if (doubleCheckPassed)
				{
					std::string date = getDate(line);
					std::string time = getTime(line);
					double* nums = getDoubles(line);


					loadData(records, date, time, nums); //if all checks passed, load the data
					size++;
				}
			}
		}

		lineNumber++;
	}

	for (int i = size - 1; i >= 0; --i)
	{
		std::cout << records->get(i) << std::endl;
	}

	return 0;
}

//date check
bool checkDate(std::string line, std::string date, int lineNumber)
{
	std::string thisLineDate = getDate(line);

	if (thisLineDate != date)
	{
		std::cout << "Non-matching date stamp " << thisLineDate << " at line " << lineNumber + 1 << "." << std::endl;
		return false;
	}

	return true;
}

//timestamp check, uses a set to verify if a timestamp exists already
bool checkTimeStamp(std::string line, std::set<std::string>& timeStamps, int lineNumber)
{
	try
	{
		std::string timeStamp = getTime(line);

		//if the element does not exist in the set, add it, otherwise print error
		if (timeStamps.count(timeStamp) < 1)
		{
			timeStamps.insert(timeStamp);
			return true;
		}
		else {

			std::cout << "Duplicate timestamp " << timeStamp << " at line " << lineNumber + 1 << "." << std::endl;
			return false;
		}
	}
	catch (...) {}

	return false;
}

//nonzero double value check
bool checkDoubles(std::string line, int lineNumber)
{
	double* data = getDoubles(line);

	for (int i = 0; i < 16; ++i)
	{
		if (data[i] <= 0)
		{
			std::cout << "Invalid floating-point data at line " << lineNumber + 1 << "." << std::endl;
			return false;
		}
	}
	
	delete[] data; // delete data after checking values
	return true;
}

//method that returns the date from a line of data
std::string getDate(std::string line)
{
	std::string date = line.substr(0, line.find(','));
	return date;
}

//method that returns the time from a line of data
std::string getTime(std::string line) 
{
	std::string noDate = line.substr(line.find(',') + 1);
	std::string timeStamp = noDate.substr(0, noDate.find(','));

	return timeStamp;
}

//method to acquire all double values from line of data
double* getDoubles(std::string line)
{
	double* nums = new double[16];
	std::string noDate = line.substr(line.find(',') + 1);
	std::string noDateNoTime = noDate.substr(noDate.find(',') + 1);

	std::stringstream ss(noDateNoTime);
	double d = 0.0;
	int i = 0;

	while (ss >> d)
	{
		nums[i] = d;

		if (ss.peek() == ',') ss.ignore();

		++i;
	}

	return nums;
}

//method that loads all data into a DrillingRecord once acquired and adds it to DrillingRecordArray
void loadData(DrillingRecordArray* arr, std::string date, std::string time, double* doubleArray)
{
	DrillingRecord* record = new DrillingRecord;

	record->addString(date);
	record->addString(time);

	for (int i = 0; i < 16; ++i)
	{
		record->addNum(doubleArray[i]);
	}

	arr->add(*record);

	delete[] doubleArray; //delete array now that we have copied the info over
}
