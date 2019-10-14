#include "DrillingRecordComparator.h"
#include "DrillingRecord.h"


DrillingRecordComparator::DrillingRecordComparator(unsigned int column)
{
	this->column = column;
}

int DrillingRecordComparator::compare(const DrillingRecord& item1, const DrillingRecord& item2) const
{
	//if first or second column, compare strings
	if (this->column < 2)
	{
		std::string first = item1.getString(column);
		std::string second = item2.getString(column);
		
		if (first.compare(second) < 0)
		{
			return -1;
		}
		else if (first.compare(second) > 0)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	//else compare doubles
	else
	{
		double first = item1.getNum(column - 2);
		double second = item2.getNum(column - 2);

		if (first < second) return -1;

		else if (second < first) return 1;

		else return 0;
	}
}