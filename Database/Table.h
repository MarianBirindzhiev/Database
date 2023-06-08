#pragma once
#include "Column.h"
#include <iomanip>
class Table
{
public:
	void print()
	{
		std::vector<size_t> columnWidth(dataTable.size(),0);
		size_t maxRow = getMaxNumberRow();

		for (size_t j = 0; j < dataTable.size(); j++)
		{
			for (size_t i = 0; i < maxRow; i++)
			{
				if (columnWidth[j] < dataTable[j]->printDataAtIndex(i).length())
					columnWidth[j] = dataTable[j]->printDataAtIndex(i).length();
			}
		}


		for (size_t row = 0; row < maxRow; row++)
		{
			for (size_t col = 0; col < dataTable.size(); col++)
			{
				std::cout << std::setw(columnWidth[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			std::cout << '\n';

		}
	}

	size_t getMaxNumberRow()
	{
		size_t max = 0;
		for (Column* col : dataTable)
			if (max < col->getSize())
				max = col->getSize();

		return max;
	}

	void addColumn(Column* col)
	{
		dataTable.push_back(col);
	}

private:

	std::vector<Column*> dataTable;

};