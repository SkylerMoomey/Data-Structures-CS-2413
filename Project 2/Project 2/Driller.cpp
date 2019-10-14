#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ResizableArray.h"
#include "DrillingRecord.h"
#include "DrillingRecordComparator.h"
#include "Exceptions.h"
#include "Search.h"
#include "Sorter.h"

//error checking method
bool checkDate(std::string line, std::string date, int lineNumber);
bool checkDoubles(std::string line, int lineNumber);

//methods which collect important data from files
std::string getDate(std::string line);
std::string getTime(std::string line);
double* getDoubles(std::string line);

//file input and file loading methods
void loadData(ResizableArray<DrillingRecord>* arr, std::string date, std::string time, double* doubleArray);
ResizableArray<DrillingRecord>* dataInputLoop();
ResizableArray<DrillingRecord>* loadFile(std::ifstream& fileName, int fileNumber, ResizableArray<DrillingRecord>* arr);

//user menu and output,sorting,searching methods
void userMenu(ResizableArray<DrillingRecord>* arr);
void printToStandardOutput(ResizableArray<DrillingRecord>* arr);
void printToFile(ResizableArray<DrillingRecord>* arr, std::ofstream* file);

void find(ResizableArray<DrillingRecord>* arr, int column, int sortedColumn, std::string key);
void find(ResizableArray<DrillingRecord>* arr, int column, int sortedColumn, double key);

//necessary global variables
long numLinesRead = 0;
long numValidLinesRead = 0;

int main()
{
	//call data input loop and return a ResizableArray with data from all files
	ResizableArray<DrillingRecord>* arr = dataInputLoop();

	//user ResizableArray to allow user to perform operations
	if (arr->getSize() > 0)
	{
		userMenu(arr);

		std::cout << "Thanks for using Driller." << std::endl;
	}
	return 0;
}

//controller for input loop.
ResizableArray<DrillingRecord>* dataInputLoop()
{
	ResizableArray<DrillingRecord>* arr = new ResizableArray<DrillingRecord>();
	std::cout << "Enter data file name: ";
	std::string input = "";
	std::getline(std::cin, input);
	std::ifstream inFile;

	int fileNumber = 0;


		while (input != "")
		{
			inFile.open(input);

			//checks that file exists
			if (!inFile.is_open())
			{
				std::cout << "File is not available." << std::endl;
			}

			else
			{
				//start parsing file
				arr = loadFile(inFile, fileNumber, arr);
				inFile.close(); //close file when done
				fileNumber++;
			}

			std::cout << "Enter data file name: ";
			std::getline(std::cin, input);
		}

	return arr;
}

ResizableArray<DrillingRecord>* loadFile(std::ifstream& fileName, int fileNumber, ResizableArray<DrillingRecord>* records)
{
	std::string line;
	std::string date;
	int lineNumber = 0;

	std::getline(fileName, line); //read in and throw out first line

	bool firstLine = true;
	long preReadSize = records->getSize();//update this once per file to match
	DrillingRecordComparator comp(1); //comparator to search for timestamps in old data

	while (std::getline(fileName, line))
	{
		if (firstLine)
		{
			date = getDate(line);
			firstLine = false;

			if (fileNumber > 0)
			{
				//check that first line date matches date of first index in records
				if (date.compare(records->get(0).getString(0)) != 0)
				{
					std::cout << "Date mismatch; file closed" << std::endl;
					numLinesRead++;
					return records; //if date check fails, return and halt file upload
				}
			}
		}

		bool dateCheckPassed = checkDate(line, date, lineNumber);

		if (dateCheckPassed)
		{
			DrillingRecord currentLine;
			std::string time = getTime(line);
			currentLine.addString(date);
			currentLine.addString(time);

			long long index = linearSearch(currentLine, *records, comp);

			if (index < 0) //not present, check doubles, then add to list
			{

				bool doubleCheckPassed = checkDoubles(line, lineNumber);

				if (doubleCheckPassed)
				{
					std::string date = getDate(line);
					std::string time = getTime(line);
					double* nums = getDoubles(line);

					numValidLinesRead++; //if all checks passed, increment number of valid lines read
					loadData(records, date, time, nums); //if all checks passed, load the data
				}
			}

			else if (index < preReadSize) // if present in old data, check doubles, delete old data, then add
			{
				bool doubleCheckPassed = checkDoubles(line, lineNumber);

				if (doubleCheckPassed)
				{
					std::string date = getDate(line);
					std::string time = getTime(line);
					double* nums = getDoubles(line);

					numValidLinesRead++; //still increment valid data even though size will not be incremented

					try
					{
						records->removeAt((long)index);
						preReadSize--; //decrement OG size because there is now one less element present in old data
					}
					catch (ExceptionIndexOutOfRange* e)
					{
						delete e;
					}

					loadData(records, date, time, nums); //if all checks passed, load the data
				}
			}

			else // index > preReadSize, print timeStamp error message
			{
				std::cout << "Duplicate timestamp " << getTime(line) << " at line " << lineNumber + 1 << "." << std::endl;
			}
		}

		lineNumber++;
		numLinesRead++;
	}

	return records;
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


//checks for negative zero values
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
void loadData(ResizableArray<DrillingRecord>* arr, std::string date, std::string time, double* doubleArray)
{
	DrillingRecord* record = new DrillingRecord;

	record->addString(date);
	record->addString(time);

	for (int i = 0; i < 16; ++i)
	{
		record->addNum(doubleArray[i]);
	}

	try
	{
		arr->add(*record);
	}
	catch (ExceptionIndexOutOfRange* e)
	{
		delete e;
	}

	delete[] doubleArray; //delete array now that we have copied the info over
}

//------------------------------------------------------------------------------
//data output methods to follow data input methods

void userMenu(ResizableArray<DrillingRecord>* arr)
{
	//by default, ResizableArray sorted on timeStamps, this will update each time it is sorted
	int columnCurrentlySorted = 1;
	//sort arr for user manipulation on timeStamps
	DrillingRecordComparator comp(1);
	Sorter<DrillingRecord>::sort(*arr, comp);

	std::cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << std::endl;

	std::string userInput = "";
	std::getline(std::cin, userInput);

	while (userInput != "q")
	{
		if (userInput == "o")
		{
			std::string fileName = " ";
			std::ofstream* outputFile = new std::ofstream();

			while (fileName != "")
			{
				std::cout << "Enter output file name: ";
				std::getline(std::cin, fileName);

				if (fileName == "")
				{
					printToStandardOutput(arr);
				}
				else
				{
					outputFile->open(fileName);

					if (!outputFile->is_open())
					{
						std::cout << "File is not available." << std::endl;
					}

					printToFile(arr, outputFile);
					outputFile->close();
					
					fileName = ""; //end output file loop
				}

			}
			
			delete outputFile;
		}
		
		if (userInput == "s")
		{
			std::cout << "Enter sort field (0-17): " << std::endl;

			int column = -1;
			std::cin >> column;
			std::getline(std::cin, userInput); //read in newline

			if (column >= 0 && column < 18)
			{
				DrillingRecordComparator comp01(column);
				Sorter<DrillingRecord>::sort(*arr, comp01);
				columnCurrentlySorted = column; //update currently sorted column
			}
		}

		if (userInput == "f")
		{
			std::cout << "Enter search field (0-17): " << std::endl;

			int column = -1;
			std::cin >> column;
			std::getline(std::cin, userInput); //read in newline

			if (column >= 0 && column < 2)
			{
				std::cout << "Enter exact text on which to search: " << std::endl;
				std::string text = "";
				std::getline(std::cin, text);

				if (text != "")
				{
					find(arr, column, columnCurrentlySorted, text);
				}
			}

			else if (column > 2 && column < 18)
			{
				std::cout << "Enter positive value: " << std::endl;
				double value = 0;

				std::cin >> value;

				if (std::cin.fail())
				{
					std::cin.clear();
					std::getline(std::cin, userInput);
				}

				else
				{
					find(arr, column, columnCurrentlySorted, value);
					std::getline(std::cin, userInput);
				}
			}
		}

		std::cout << "Enter (o)utput, (s)ort, (f)ind, or (q)uit: " << std::endl;
		std::getline(std::cin, userInput);
	}
}

//standard output printer
void printToStandardOutput(ResizableArray<DrillingRecord>* arr)
{
	for (unsigned long i = 0; i < arr->getSize(); i++)
	{
		std::cout << arr->get(i) << std::endl;
	}

	std::cout << "Data lines read: " << numLinesRead << "; Valid drilling records read: " << numValidLinesRead << 
		"; Drilling records in memory: " << arr->getSize() << std::endl;
}

//file output printer
void printToFile(ResizableArray<DrillingRecord>* arr, std::ofstream *file)
{
	for (unsigned long i = 0; i < arr->getSize(); i++)
	{
		*file << arr->get(i) << std::endl;
	}

	*file << "Data lines read: " << numLinesRead << "; Valid drilling records read: " << numValidLinesRead <<
		"; Drilling records in memory: " << arr->getSize() << std::endl;

}

//searching method
void find(ResizableArray<DrillingRecord>* arr, int column, int sortedColumn, std::string key)
{
	DrillingRecordComparator comp(column);
	DrillingRecord record;
	record.setString(key, column); //create new drilling record with same data as key
	long long numFound = 0;

	if (column == sortedColumn)
	{
		long long index = binarySearch(record, *arr, comp);

		if (index >= 0) //make sure it's a valid index
		{
			long long next = index; //set next as key of first index

			while ((unsigned long)next < arr->getSize() && arr->get((unsigned long)next).getString(column) == key)
			{
				std::cout << arr->get((unsigned long)next) << std::endl;
				next++;
				numFound++;
			}
		}
	}
	else
	{
		long long index = linearSearch(record, *arr, comp);

		while (index >= 0 && (unsigned long)index < arr->getSize())
		{
			numFound++;
			std::cout << arr->get(index) << std::endl;

			index = linearSearch(record, *arr, comp, index + 1);
		}
	}
	
	std::cout << "Drilling records found: " << numFound << "." << std::endl;
}

//searching method for doubles
void find(ResizableArray<DrillingRecord>* arr, int column, int sortedColumn, double key)
{
	DrillingRecordComparator comp(column);
	DrillingRecord record;
	record.setNum(key, column - 2); //create new drilling record with same data as key
	long long numFound = 0;

	if (column == sortedColumn)
	{
		long long index = binarySearch(record, *arr, comp);

		if (index >= 0) //make sure it's a valid index
		{
			long long next = index; //set next as key of first index

			while ((unsigned long)next < arr->getSize() && arr->get((unsigned long)next).getNum(column - 2) == key)
			{
				std::cout << arr->get((unsigned long)next) << std::endl;
				next++;
				numFound++;
			}
		}
	}
	else
	{
		long long index = linearSearch(record, *arr, comp);

		while (index >= 0 && (unsigned long)index < arr->getSize())
		{
			numFound++;
			std::cout << arr->get(index) << std::endl;

			index = linearSearch(record, *arr, comp, index + 1);
		}
	}

	std::cout << "Drilling records found: " << numFound << "." << std::endl;
}
