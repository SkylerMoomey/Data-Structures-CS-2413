// Driller.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>

bool checkDate(std::string& line, std::string date, int lineNumber);
bool addTimeStamp(std::string& line, std::set<std::string>& timeStamps, int lineNumber);
bool checkZeroEntries(std::string& line, int lineNumber);
void reprintWithSemicolons(std::string& line);
std::string setDate(std::string line);

int main()
{
	std::string line = "";

	//collect and toss out first line
	std::getline(std::cin, line);

	std::string date = "";
	bool firstLine = true;
	int lineNumber = 1;

	//set for unique time stamps
	std::set<std::string> timeStampSet;

	while (std::getline(std::cin, line))
	{
		//sets the date if this is the first line read into the program
		if (firstLine)
		{
			date = setDate(line);
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

				//if all valid entries, reprints line with semicolons
				if (zeroEntriesCheckPassed)
				{
					reprintWithSemicolons(line);
				}
			}
		}

		lineNumber++;
	}



	return 0;
}

//sets the date according to the date in the first line of data
std::string setDate(std::string date) {

	int indexOfFirstComma = (int)date.find(",");
	return date.substr(0, indexOfFirstComma);
}

//compares the date in each line to the date supplied to the method, returns true is correct date, false otherwise
bool checkDate(std::string& line, std::string date, int lineNumber) {

	//pulls out information up to first comma
		std::string lineDate = line.substr(0, line.find(","));

		//date check, return false if it doesn't match
		if (lineDate != date)
		{
			std::cout << "Non-matching date stamp " << lineDate << " at line " << lineNumber << "." << std::endl;
			return false;
		}

		return true;
}

//method to add a lines time stamp to a set and check if it already exists in the set
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

				std::cout << "Duplicate time stamp " << timeStampOnly << " at line " << lineNum << "." << std::endl;
				return false;
			}
		}
		catch (...) {}

	return false;
}

bool checkZeroEntries(std::string& line, int lineNumber)
{
	//cut off date
	std::string withoutDate = line.substr(line.find(",") + 1);

	//cut off time
	std::string withoutTimeOrDate = withoutDate.substr(withoutDate.find(",") + 1);

	/*
	algorithm for converting a comma delimited string to an array of floats inspired
	by a stack overflow post by user randominstanceOfLivingThing
	https://stackoverflow.com/questions/36758821/comma-separated-floats-in-c

	lines 126 to 139
	*/
	std::stringstream lineWithCommas(withoutTimeOrDate);
	std::vector<float> numbers(0);

	float i;

	while (lineWithCommas >> i)
	{
		numbers.push_back(i);

		if (lineWithCommas.peek() == ',') 
		{ 
			lineWithCommas.ignore();
		}
	}

	for (unsigned int i = 0; i < numbers.size(); ++i) {

		if (numbers.at(i) <= 0.0)
		{
			std::cout << "Invalid floating-point data at line " << lineNumber << "." << std::endl;
			return false;
		}
	}

	return true;
}

void reprintWithSemicolons(std::string& line)
{
	for (std::string::size_type i = 0; i < line.size(); ++i)
	{
		if (line[i] == ',') std::cout << ";";

		else std::cout << line[i];
	}

	std::cout << "\n";
}

