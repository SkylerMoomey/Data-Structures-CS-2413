#include "DrillingRecord.h"
#include "DrillingRecordComparator.h"


void dateTest();
void timeStampTest();
void doubleTest();

int main()
{

	dateTest();
	timeStampTest();
	doubleTest();

	return 0;
}

bool assert(int item1, int item2)
{
	return (item1 == item2);
}

void dateTest()
{
	DrillingRecordComparator comp(0);
	DrillingRecord r1;
	DrillingRecord r2;

	r1.setString("blahblah", 0);
	r2.setString("blahblah", 0);

	int greaterOrLesser = comp.compare(r1, r2);

	if (assert(0, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 0: r1 == r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 0: r1 == r2" << std::endl;
	}

	r1.setString("alahblah", 0);
	r2.setString("blahblah", 0);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(-1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 0: r1 < r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 0; r1 < r2" << std::endl;
	}

	r1.setString("blahblah", 0);
	r2.setString("alahblah", 0);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 0: r1 > r2" << std::endl;
	}
	else
	{
		std::cout << "Test Failure @ Column 0: r1 > r2" << std::endl;
	}

}

void timeStampTest()
{
	DrillingRecordComparator comp(1);
	DrillingRecord r1;
	DrillingRecord r2;

	r1.setString("blahblah", 1);
	r2.setString("blahblah", 1);

	int greaterOrLesser = comp.compare(r1, r2);

	if (assert(0, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 1: r1 == r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 1: r1 == r2" << std::endl;
	}

	r1.setString("alahblah", 1);
	r2.setString("blahblah", 1);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(-1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 1: r1 < r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 1; r1 < r2" << std::endl;
	}

	r1.setString("blahblah", 1);
	r2.setString("alahblah", 1);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 1: r1 > r2" << std::endl;
	}
	else
	{
		std::cout << "Test Failure @ Column 1: r1 > r2" << std::endl;
	}
}

void doubleTest()
{
	DrillingRecordComparator comp(2);
	DrillingRecord r1;
	DrillingRecord r2;

	r1.setNum(1, 0);
	r2.setNum(1, 0);

	int greaterOrLesser = comp.compare(r1, r2);

	if (assert(0, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 2: r1 == r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 2: r1 == r2" << std::endl;
	}

	r1.setNum(0, 0);
	r2.setNum(1, 0);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(-1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 2: r1 < r2" << std::endl;
	}

	else
	{
		std::cout << "Test Failed @ Column 2; r1 < r2" << std::endl;
	}

	r1.setNum(1, 0);
	r2.setNum(0, 0);

	greaterOrLesser = comp.compare(r1, r2);

	if (assert(1, greaterOrLesser))
	{
		std::cout << "Test Successful @ Column 2: r1 > r2" << std::endl;
	}
	else
	{
		std::cout << "Test Failure @ Column 2: r1 > r2" << std::endl;
	}
}

