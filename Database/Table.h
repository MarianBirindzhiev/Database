#pragma once
#include "Column.h"
#include "Factory.h"
#include <fstream>
#include <sstream>
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