#include "Table.h"

Table::Table(const std::string& name)
{
	if (!isStringCorrect(name))
		throw std::exception("the given table name is invalid");

	this->name = name;
}


Table::Table(const std::string& name, const std::string& fileName)
{
	if (!isStringCorrect(name))
		throw std::exception("the given table name is invalid");
	if (!isStringCorrect(fileName))
		throw std::exception("the given fileName is incorrect");

	this->name = name;
	this->fileName = fileName;

	setData();
}


Table::~Table()
{
	clear();
}


void Table::print()
{
	std::vector<size_t> column = columnWidth();
	size_t maxRow = getMaxNumberRow();

	const int columnsPerPage = 5;
	int startColumn = 0;

	std::string command;
	do
	{
		int endColumn = std::min(startColumn + columnsPerPage, static_cast<int>(dataTable.size()));

		for (size_t row = 0; row < maxRow; row++)
		{
			for (size_t col = startColumn; col <endColumn; col++)
			{
				std::cout << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			std::cout << '\n';
		}

		std::cout << "Commands: (next), (previous), (stop)\n";
		std::cin >> command;

		if (command == "next")
		{
			if (endColumn < dataTable.size())
				startColumn = endColumn;
			else
				std::cout << "You are already on the last page\n";
		}
		else if (command == "previous")
		{
			if (startColumn > 0)
				startColumn = std::max(startColumn - columnsPerPage, 0);
			else
				std::cout << "You are already on the first page\n";
		}
		else if (command != "stop")
			std::cout << "Invalid command";

	} while (command !="stop");

}


void Table::saveInFile()
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
			file << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
		}
		file << '\n';

	}
	file.close();

}


void Table::addColumn(Column* col)
{
	dataTable.push_back(col);
}


void Table::addColumn(const std::string& type)
{
	if (!isStringCorrect(type))
		throw std::exception("the given type is invalid");

	try
	{
		dataTable.push_back(Factory::getFactory().createColumn(type));
		size_t row = getMaxNumberRow();

		for (size_t i = 0; i < row; i++)
		{
			dataTable[dataTable.size() - 1]->addElement("NULL");
		}
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Failed to allocate memory: " << e.what() << '\n';
		clear();
	}

}


void Table::describe()
{
	for (const auto& col : dataTable)
		std::cout << col->getType() << ' ';
	std::cout << '\n';
}


void Table::setFileName(const std::string& fileName)
{
	if (!isStringCorrect(fileName))
		throw std::exception("the given fileName is incorrect");

	this->fileName = fileName;
}


void Table::setData()
{
	std::ifstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file");

	std::string line;
	std::getline(file, line);

	std::istringstream iss(line);
	std::string type;

	try
	{
		while (iss >> type)
			dataTable.push_back(Factory::getFactory().createColumn(type));

	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Failed to allocate memory: " << e.what() << '\n';
		clear();
	}

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


void Table::select(size_t columnIndex, const std::string& value)
{
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is invalid");

	std::vector<int> helper = rowHelper(columnIndex, value);
	std::vector<size_t> column = columnWidth();

	const int columnsPerPage = 5;
	int startColumn = 0;

	std::string command;
	do
	{
		int endColumn = std::min(startColumn + columnsPerPage, static_cast<int>(dataTable.size()));

		for (int row : helper)
		{
			for (size_t col = startColumn; col < endColumn; col++)
			{
				std::cout << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | ";
			}
			std::cout << '\n';
		}
		std::cout << "Commands: (next), (previous), (stop)\n";
		std::cin >> command;

		if (command == "next")
		{
			if (endColumn < dataTable.size())
				startColumn = endColumn;
			else
				std::cout << "You are already on the last page\n";
		}
		else if (command == "previous")
		{
			if (startColumn > 0)
				startColumn = std::max(startColumn - columnsPerPage, 0);
			else
				std::cout << "You are already on the first page\n";
		}
		else if (command != "stop")
			std::cout << "Invalid command";



	} while (command != "stop");
}


Table* Table::select_onto(const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value)
{
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is invalid");

	Table* resulTable = new Table("resultTable");
	std::vector<int> helper = rowHelper(columnIndex, value);

	for (int col : columnIndexes)
		resulTable->addColumn(dataTable[col]->getType());

	for (int row : helper)
	{
		for (size_t col = 0; col < columnIndexes.size(); col++)
		{
			resulTable->dataTable[col]->addElement(dataTable[columnIndexes[col]]->printDataAtIndex(row));
		}
	}
	return resulTable;

}


void Table::remove(size_t columnIndex, const std::string& value)
{
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is invalid");

	std::vector<int> helper = rowHelper(columnIndex, value);

	for (size_t row = helper.size() - 1; row != -1; row--)
	{
		for (size_t col = 0; col < dataTable.size(); col++)
		{
			dataTable[col]->removeDataAtIndex(helper[row]);
		}
	}
}


void Table::update(size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue)
{
	if (!isStringCorrect(searchValue) || !isStringCorrect(targetValue))
		throw std::exception("the given value is invalid");

	if (!isColumnIndexCorrect(searchColumnIndex) || !isColumnIndexCorrect(targetColumnIndex))
		throw std::exception("the given column index is invalid");

	std::vector<int> helper = rowHelper(searchColumnIndex, searchValue);

	for (int row : helper)
		dataTable[targetColumnIndex]->update(targetValue, row);

}


void Table::insert(const std::vector<std::string>& values)
{
	if (values.size() != dataTable.size())
		throw std::exception("there are not enough values");

	for (size_t i = 0; i < dataTable.size(); i++)
		dataTable[i]->addElement(values[i]);
}


void Table::clear()
{
	for (auto& col : dataTable)
		delete col;
}


size_t Table::getMaxNumberRow()
{
	size_t max = 0;
	for (Column* col : dataTable)
		if (max < col->getSize())
			max = col->getSize();

	return max;
}


std::vector<size_t> Table::columnWidth()
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


std::vector<int> Table::rowHelper(size_t columnIndex, const std::string& value)
{
	std::vector<int> rowIndexes;
	for (size_t i = 0; i < dataTable[columnIndex]->getSize(); i++)
	{
		if (dataTable[columnIndex]->printDataAtIndex(i) == value)
			rowIndexes.push_back(i);
	}
	return rowIndexes;
}