#pragma once
#define NOMINMAX
#include "Column.h"
#include "Factory.h"
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <limits>
#include <string>

class Table
{
public:
	Table(const std::string& name, const std::string& fileName)
	{
		if (!isNameCorrect(name))
			throw std::exception("the given table name is invalid");
		if (!isNameCorrect(fileName))
			throw std::exception("the given fileName is incorrect");

		this->name = name;
		this->fileName = fileName;
	}

	~Table()
	{
		clear();
	}

	void print() const
	{
		std::vector<size_t> column = columnWidth();
		size_t maxRow = getMaxNumberRow();

		for (size_t row = 0; row < maxRow; row++)
		{
			for (size_t col = 0; col < dataTable.size(); col++)
			{
				std::cout << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			std::cout << '\n';
		}
		
	}
	

	void saveInFile() const
	{
		std::ofstream file(this->fileName);
		if (!file)
			throw std::exception("could not open the file");

		for (const auto& col : dataTable)
			file << col->getType() << ' ';
		file << '\n';

		std::vector<size_t> column = columnWidth();
		size_t maxRow = getMaxNumberRow();

		for (size_t row = 0; row < maxRow; row++)
		{
			for (size_t col = 0; col < dataTable.size(); col++)
			{
				file<< std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			file << '\n';

		}
		file.close();

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

	void addColumn(const std::string& type)
	{
		dataTable.push_back(Factory::getFactory().createColumn(type));
		size_t row = getMaxNumberRow();

		for (size_t i = 0; i < row; i++)
		{
			dataTable[dataTable.size() - 1]->addElement("NULL");
		}
	}


	void describe() const
	{
		for (const auto& col : dataTable)
			std::cout << col->getType() << ' ';
		std::cout << '\n';
	}

	std::string const getName() const { return this->name; }

	const std::string getFileName() const { return this->fileName; }

	void setFileName(const std::string fileName)
	{
		if (!isNameCorrect(fileName))
			throw std::exception("the given fileName is incorrect");
		
		this->fileName = fileName;
	}

	void setColumnTypes()
	{
		std::ifstream file(this->fileName);
		if (!file)
			throw std::exception("could not open the file");

		std::string line;
		std::getline(file, line);

		std::istringstream iss(line);
		std::string type;
		while (iss >> type)
			dataTable.push_back(Factory::getFactory().createColumn(type));

		file.close();
	}

	void setData()
	{
		setColumnTypes();
		
		std::ifstream file(this->fileName);
		if (!file)
			throw std::exception("could not open the file");

		std::string line;
		std::getline(file, line);

		while (std::getline(file, line))
		{
			std::istringstream iss(line);
			std::string type;
			int i = 0;
			while (iss >> type)
			{
				if (type != "|")
				{
					dataTable[i++]->addElement(type);
				}
			}
		}
		file.close();

	}

	void select(size_t columnIndex,const std::string& value)
	{
		std::vector<int> helper = rowHelper(columnIndex, value);
		std::vector<size_t> column = columnWidth();
		for (int row : helper)
		{
			for (size_t col = 0; col < dataTable.size(); col++)
			{
				std::cout << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			std::cout << '\n';
		}
	}

	std::vector<int> rowHelper(size_t columnIndex,const std::string& value)
	{
		std::vector<int> rowIndexes;
		for (size_t i = 0; i < dataTable[columnIndex]->getSize(); i++)
		{
			if (dataTable[columnIndex]->printDataAtIndex(i) == value)
				rowIndexes.push_back(i);
		}
		return rowIndexes;
	}

	void remove(size_t columnIndex, const std::string& value)
	{
		std::vector<int> helper = rowHelper(columnIndex, value);
		
		for (size_t row = helper.size() - 1; row != -1; row--)
		{
			for (size_t col = 0; col < dataTable.size(); col++)
			{
				dataTable[col]->removeDataAtIndex(helper[row]);
			}
		}
	}

	void update(size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue)
	{
		std::vector<int> helper = rowHelper(searchColumnIndex, searchValue);

		for (int row : helper)
			dataTable[targetColumnIndex]->update(targetValue, row);

	}

	void insert(const std::vector<std::string> values)
	{
		if (values.size() != dataTable.size())
			throw std::exception("there are not enough values");

		for (size_t i = 0; i < dataTable.size(); i++)
			dataTable[i]->addElement(values[i]);
	}


private:
	std::string name;
	std::vector<Column*> dataTable;
	std::string fileName;

	void clear()
	{
		for (auto& col : dataTable)
			delete col;
	}

	bool isNameCorrect(const std::string& name) { return name != ""; }

	std::vector<size_t> columnWidth() const
	{
		std::vector<size_t> columnWidth(dataTable.size(), 0);
		size_t maxRow = getMaxNumberRow();

		for (size_t j = 0; j < dataTable.size(); j++)
		{
			for (size_t i = 0; i < maxRow; i++)
			{
				if (columnWidth[j] < dataTable[j]->printDataAtIndex(i).length())
					columnWidth[j] = dataTable[j]->printDataAtIndex(i).length();
			}
		}

		return columnWidth;
	}
};