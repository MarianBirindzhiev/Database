#pragma once
#include "Column.h"

class Table
{
public:
	Table(const std::string& name)
		:name(name) {}

	void print() const
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

	size_t getMaxNumberRow() const
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


	void describe() const
	{
		for (const auto& col : dataTable)
			std::cout << col->getType() << '\t';
	}
	std::string const getName() const { return this->name; }


private:
	std::string name;
	std::vector<Column*> dataTable;

};