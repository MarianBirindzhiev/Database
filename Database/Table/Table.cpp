#include "../Table/Table.h"

/// Constructor with name
/// Validates the given table name and sets it as the name of the table
Table::Table(const std::string& name)
{
	if (!isStringCorrect(name))
		throw std::exception("the given table name is invalid");

	this->name = name;
}


/// Constructor with name and file name
/// Validates the given table name and file name
/// Sets the name and file name of the table
/// Loads data from the file and populates the table
Table::Table(const std::string& name, const std::string& fileName)
{
	if (!isStringCorrect(name))
		throw std::exception("the given table name is invalid");
	if (!isStringCorrect(fileName))
		throw std::exception("the given fileName is incorrect");

	this->name = name;
	this->fileName = fileName;

	setData(); // Load data from file
}

/// Copy constructor
/// Creates a copy of the given Table object.
/// Initializes name and fileName; clones Columns for deep copying.
Table::Table(const Table& other)
	:name(other.name), fileName(other.fileName), dataTable()
{
	for(const auto& col : other.dataTable)
		dataTable.push_back(col->clone());
}

// Assignment operator
/// Assigns values from another Table object to this one.
/// Handles self-assignment, clears existing data, and clones Columns for deep copying.
Table& Table::operator=(const Table& other)
{
	if(this != &other)
	{
		clear();

		this->name = other.name;
		this->fileName = other.fileName;

		for(const auto& col : other.dataTable)
			dataTable.push_back(col->clone());
	}

	return *this;
}

/// Destructor
/// Clears the table by deleting all columns
Table::~Table()
{
	clear(); 
}


/// Print the table
/// Prints the table in a format through which it is possible to change pages
void Table::print()
{
	std::vector<size_t> column = columnWidth();
	size_t maxRow = getMaxNumberRow();

	const int columnsPerPage = 5;
	int startColumn = 0;
	std::cout << '\n';
	std::string command;
	do
	{
		int endColumn = std::min(startColumn + columnsPerPage, static_cast<int>(dataTable.size())); // Тakes the last column we print to

		for (size_t row = 0; row < maxRow; row++)
		{
			for (size_t col = startColumn; col < endColumn; col++)
			{
				std::cout << std::setw(column[col] + 2) << std::left << dataTable[col]->printDataAtIndex(row) << " | "; // Prints the data rows with proper offset

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
			std::cout << "Invalid command\n";

	} while (command != "stop");

}


/// Save the table in a file
/// Writes the table data to the file in a formatted manner
void Table::saveInFile()
{
	std::ofstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file");

	// Write column types to the file
	for (const auto& col : dataTable)
		file << col->getType() << ' ';
	file << '\n';

	std::vector<size_t> column = columnWidth();
	size_t maxRow = getMaxNumberRow();

	// Write data rows to the file
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


/// Add a column to the table
/// Adds the given column object to the table
void Table::addColumn(Column* col)
{
	dataTable.push_back(col);
}


/// Add a column to the table by type
/// Validates the given column type and creates a new column object of that type
/// Adds the newly created column object to the table
/// Initializes the column with "NULL" values for existing rows in the table
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
		clear(); // Clean up
	}
}


/// Print the column types of the table
/// Prints the types of columns present in the table
void Table::describe()
{
	for (const auto& col : dataTable)
		std::cout << col->getType() << ' ';

	std::cout << '\n';
}


/// Set the file name for the table
/// Validates the given file name and sets it as the file name of the table
void Table::setFileName(const std::string& fileName)
{
	if (!isStringCorrect(fileName))
		throw std::exception("the given fileName is incorrect");

	this->fileName = fileName;
}


/// Set the data of the table from a file
/// Reads the data from the file and populates the table accordingly
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
		clear(); // Clean up
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


/// Select rows based on a column value
/// Validates the given column index and value
/// Prints the selected rows along with a possibility to change pages
void Table::select(size_t columnIndex, const std::string& value)
{
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is out of range");

	std::vector<int> helper = rowHelper(columnIndex, value);
	std::vector<size_t> column = columnWidth();

	const int columnsPerPage = 5;
	int startColumn = 0;
	std::cout << '\n';
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

///Create a new table by selecting specific columns and rows from the current table.
///- name: The name of the new table.
///- columnIndexes: A vector of column indexes to be included in the new table.
/// - columnIndex: The index of the column to search for the value.
/// - value: The value to search for in the specified column.
/// Throws an exception if the value is invalid (not a correct string)
/// or if the column index is invalid.
/// Creates a new table with the given name, adds columns to it based on the specified column indexes,
///and populates it with values from the rows that match the search criteria.
/// Returns a pointer to the newly created table.
Table* Table::select_onto(const std::string& name, const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value)
{
	// Validate the value to ensure it is a valid string
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	// Validate the column index to ensure it is a valid index
	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is invalid");

	// Create a new result table with the given name
	Table* resultTable = new(std::nothrow) Table(name);
	if(resultTable == nullptr)
		throw std::bad_alloc();

	// Add columns to the result table based on the column indexes
	for (int col : columnIndexes)
		resultTable->addColumn(dataTable[col]->getType());

	// Find rows that match the search criteria and populate the result table with selected values
	std::vector<int> helper = rowHelper(columnIndex, value);
	for (int row : helper)
	{
		for (size_t col = 0; col < columnIndexes.size(); col++)
		{
			resultTable->dataTable[col]->addElement(dataTable[columnIndexes[col]]->printDataAtIndex(row));
		}
	}

	return resultTable;
}

///Remove rows from the table based on a search criteria.
/// - columnIndex: The index of the column to search for the value.
///- value: The value to search for in the specified column.
///Throws an exception if the value is invalid (not a correct string)
///or if the column index is invalid.
/// Searches for rows that match the search criteria and removes them from the table.
/// Rows are removed in reverse order to avoid shifting indices during removal.
void Table::remove(size_t columnIndex, const std::string& value)
{
	// Validate the value to ensure it is a valid string
	if (!isStringCorrect(value))
		throw std::exception("the given value is invalid");

	// Validate the column index to ensure it is a valid index
	if (!isColumnIndexCorrect(columnIndex))
		throw std::exception("the given column index is invalid");

	// Find rows that match the search criteria and remove them from the table
	std::vector<int> helper = rowHelper(columnIndex, value);
	for (size_t row = helper.size() - 1; row != -1; row--)
	{
		for (size_t col = 0; col < dataTable.size(); col++)
		{
			dataTable[col]->removeDataAtIndex(helper[row]);
		}
	}
}


///Update the values in the target column based on a search criteria.
///- searchColumnIndex: The index of the column to search for the search value.
///- searchValue: The value to search for in the search column.
///- targetColumnIndex: The index of the column to update with the target value.
///- targetValue: The value to update the target column with.
/// Throws an exception if the search value or target value is invalid (not a correct string)
/// or if the search column index or target column index is invalid.
/// Searches for rows that match the search criteria, and updates the corresponding row in the
///target column with the target value.
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
///
///Insert a new row into the table with the given values.
///- values: A vector of strings representing the values to insert into the table.
///Throws an exception if the number of values does not match the number of columns in the table.
///Adds each value to the corresponding column in the table.
void Table::insert(const std::vector<std::string>& values)
{
	if (values.size() != dataTable.size())
		throw std::exception("there are not enough values");

	for (size_t i = 0; i < dataTable.size(); i++)
		dataTable[i]->addElement(values[i]);
}


/// Clear the table
/// Deletes all columns and clears the data
void Table::clear()
{
	for (auto& col : dataTable)
	{
		delete col;
		col = nullptr;
	}
	dataTable.clear();
}

/// Calculate the maximum number of rows among all columns in the table.
///Iterates over each column in the table and compares its size with the current maximum.
///Returns the maximum number of rows found.
size_t Table::getMaxNumberRow()
{
	size_t max = 0;
	for (Column* col : dataTable)
		if (max < col->getSize())
			max = col->getSize();

	return max;
}


///Calculate the width of each column in the table.
///Initializes a vector of column widths with zeros.
///Iterates over each column and row in the table and updates the column width
///if the length of the data at the current index is greater than the current width.
///Returns a vector containing the calculated widths for each column.
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


/// Select rows based on a column value
/// Validates the given column index and value
/// Returns the row indexes where the column value matches the given value
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