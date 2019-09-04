// Driller0.2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <iomanip>

struct drillingRecord;
struct drillingArray;

drillingArray* loadData(drillingArray* drillingData, std::string line, int lineNumber);
drillingArray* doubleDrillingArray(drillingArray* currentDrillingArray);

bool addTimeStamp(std::string& line, std::set<std::string>& timeStamps, int lineNum);
bool checkZeroEntries(std::string& line, int lineNumber);
bool checkDate(std::string& line, std::string date, int lineNumber);

struct drillingRecord {

	double nums[16];
	std::string strings[2];
};
struct drillingArray {

	int capacity;
	int size;
	drillingRecord* data = NULL;
};

int main()
{
	std::string line = "";

	//collect and toss out first line
	std::getline(std::cin, line);

	std::string date = "";
	int lineNumber = 0;
	bool firstLine = true;

	std::set<std::string> timeStampSet;

	drillingArray* drillArray = new drillingArray();
	drillArray->capacity = 10;
	drillArray->data = new drillingRecord[10];
	drillArray->size = 0;

	//load all data into drillArray
	while (std::getline(std::cin, line))
	{
		//sets the date if this is the first line read into the program
		if (firstLine)
		{
			date = line.substr(0, line.find(','));
			firstLine = !firstLine;
		}

		bool dateCheckPassed = false;
		dateCheckPassed = checkDate(line, date, lineNumber);

		//if the date was matched, checks if the time stamp is correct
		if (dateCheckPassed)
		{
			bool timeStampCheckPassed = false;
			timeStampCheckPassed = addTimeStamp(line, timeStampSet, lineNumber);

			//if the time stamp is correct, checks that the floating point entries are all > 0.0
			if (timeStampCheckPassed)
			{
				bool zeroEntriesCheckPassed = false;
				zeroEntriesCheckPassed = checkZeroEntries(line, lineNumber);

				//if all valid entries, adds line to drillArray
				if (zeroEntriesCheckPassed)
				{
					drillArray = loadData(drillArray, line, drillArray->size);
				}
			}
		}
		lineNumber++;
	}

	
	for (int i = drillArray->size - 1; i >= 0; i--)
	{
		for (int j = 0; j < 2; j++)
		{
			std::cout << drillArray->data[i].strings[j] << ";";
		}

		for (int k = 0; k < 15; k++)
		{
			std::cout << std::fixed << std::setprecision(2) << drillArray->data[i].nums[k] << ";";
		}

		std::cout << drillArray->data[i].nums[15] << std::endl;
	}

	return 0;
}

drillingArray* loadData(drillingArray* drillingData, std::string line, int size)
{
	drillingRecord* thisLine = new drillingRecord;

	for (int column = 0; column < 3; column++)
	{
		//if capacity full resize
		if (size == drillingData->capacity)
		{
			drillingData = doubleDrillingArray(drillingData);
		}
		//drilling record to store the line
		if (column == 0)
		{
			//extract date
			std::string date = line.substr(0, line.find(','));
			thisLine->strings[column] = date;
		}
		else if (column == 1)
		{
			//extract time
			std::string time = line.substr(line.find(',') + 1);
			time = time.substr(0, time.find(','));
			thisLine->strings[column] = time;
		}

		//if column number is 2 or greater, load doubles
		else
		{
			std::string withoutDate = line.substr(line.find(',') + 1);
			std::string withoutDateOrTime = withoutDate.substr(withoutDate.find(',') + 1);

			std::stringstream ss(withoutDateOrTime);
			int i = 0;
			double number = 0.0;

			while (ss >> number)
			{
	
				thisLine->nums[i] = number;

				if (ss.peek() == ',') ss.ignore();

				++i;
			}
		}
	}
	drillingData->data[size] = *thisLine;
	drillingData->size++;

	return drillingData;

}

//method for resizing drillingArray structure
drillingArray* doubleDrillingArray(drillingArray* currentDrillingArray)
{
	drillingArray* tempArray = new drillingArray;
	tempArray->capacity = 2 * currentDrillingArray->capacity;
	tempArray->data = new drillingRecord[tempArray->capacity];
	tempArray->size = currentDrillingArray->size;

	//copy drillingRecord over
	for (int i = 0; i < currentDrillingArray->capacity; i++)
	{
		tempArray->data[i] = currentDrillingArray->data[i];
	}

	//delete memory locations for currentDrillingArray members
	delete[] currentDrillingArray->data;
	currentDrillingArray->data = NULL;

	//delete the memory location for currentDrillingArray
	delete currentDrillingArray;

	//return new array that's twice as big
	return tempArray;
}

bool addTimeStamp(std::string& line, std::set<std::string>& timeStamps, int lineNum)
{
	try
	{
		//cuts off date and first comma
		std::string lineNoDate = line.substr(line.find(",") + 1);
		//cuts off from the second comma to the end
		std::string timeStampOnly = lineNoDate.substr(0, lineNoDate.find(","));

		//if the element does not exist in the set, add it, otherwise print error
		if (timeStamps.count(timeStampOnly) < 1)
		{
			timeStamps.insert(timeStampOnly);
			return true;
		}
		else {

			std::cout << "Duplicate timestamp " << timeStampOnly << " at line " << lineNum + 1 << "." << std::endl;
			return false;
		}
	}
	catch (...) {}

	return false;
}

bool checkZeroEntries(std::string& line, int lineNumber)
{

	std::string noDate = line.substr(line.find(',') + 1);
	std::string noDateNoTime = noDate.substr(noDate.find(',') + 1);

	std::stringstream ss(noDateNoTime);
	double d = 0.0;

	while (ss >> d)
	{
		if (d <= 0)
		{
			std::cout << "Invalid floating-point data at line " << lineNumber + 1 << "." << std::endl;
			return false;
		}

		if (ss.peek() == ',') ss.ignore();
	}

	return true;
}

bool checkDate(std::string& line, std::string date, int lineNumber) {

	//pulls out information up to first comma
	std::string lineDate = line.substr(0, line.find(","));

	//date check, return false if it doesn't match
	if (lineDate != date)
	{
		std::cout << "Non-matching date stamp " << lineDate << " at line " << lineNumber + 1 << "." << std::endl;
		return false;
	}

	return true;
}


