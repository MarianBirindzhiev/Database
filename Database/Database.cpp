#include "Database.h"

/// Constructor for the Database class. Initializes the object by setting the file
///name and loading the data from the file.
Database::Database(const std::string& fileName) 
{
	setFileName(fileName); // Set the file name for the database
	setData(); // Load data from the file into the database
}


/// Destructor for the Database class. Clears the database by deleting all tables
///and freeing the associated memory.
Database::~Database()
{
	clear(); // Free memory by deleting all tables in the database
}


/// Load data from the file into the database. If the file doesn't exist, a new file is created. 
///Each line in the file represents a table, which is imported into the database.
void Database::setData()
{
	if (!fileExists(this->fileName))
		createFile(this->fileName); // If the file doesn't exist, create a new file

	std::ifstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file"); // Throw an exception if the file cannot be opened

	std::string line;
	while (std::getline(file, line))
	{
		if (!line.empty())
			import(line); // Import each line as a table into the database
	}

	file.close();
}


/// Set the file name for the database. It checks if the given file name is valid 
/// and throws an exception if it's not.
void Database::setFileName(const std::string& fileName)
{
	if (!isStringCorrect(fileName))
		throw std::exception("the given file name is invalid"); // Throw an exception if the given file name is invalid

	this->fileName = fileName; // Set the file name for the database
}


/// Save the database data to the file. It opens the file and writes the file names of all tables in the database to the file.
void Database::saveData()
{
	std::ofstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file"); // Throw an exception if the file cannot be opened

	for (const auto& table : tables)
		file << table->getFileName() << '\n'; // Save the file names of all tables in the database to the file

	file.close();
}


/// Print the names of all tables in the database.
void Database::showTables()
{
	for (const auto& table : tables)
		std::cout << table->getName() << ' '; // Print the names of all tables in the database

	std::cout << '\n';
}


/// Import a table into the database from the given file name. 
/// It extracts the table name from the file name and checks if a table with the same name 
/// already exists in the database.
void Database::import(const std::string& fileName)
{
	std::size_t dotPos = fileName.find('.');
	std::string tableName;

	if (dotPos != std::string::npos)
		tableName = fileName.substr(0, dotPos); // Extract the table name from the file name
	else
		throw std::exception("invalid fileName format"); // Throw an exception if the file name format is invalid

	if (contains(tableName))
		throw std::exception("There is already a table with that name in the database"); // Throw an exception if there is already a table with the same name in the database

	try
	{
		Table* table = new Table(tableName, fileName); // Create a new table with the given name and file name
		tables.push_back(table); // Add the table to the database
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Failed to allocate memory: " << e.what() << '\n';
		clear(); // If memory allocation fails, clear the database
	}
}


/// Print the contents of the table with the given name.
void Database::print(const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->print();
}


/// Print the description of the table with the given name.
void Database::describe(const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->describe();
}


/// Save the table with the given name to a file with the provided file name.
void Database::saveTable(const std::string& tableName, const std::string& fileName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->setFileName(fileName);
	wantedTable(tableName)->saveInFile();
}

/// Select rows from the table with the given name where the value
/// in the specified column matches the provided value.
void Database::select(size_t columnIndex, const std::string& value, const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->select(columnIndex, value);
}


/// Select rows from the table with the given name where the value in the 
/// specified column matches the provided value and create a new table with the selected rows.
void Database::select_onto(const std::string& name, const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value, const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	tables.push_back(wantedTable(tableName)->select_onto(name, columnIndexes, columnIndex, value));
}


/// Add a new column with the specified type to the table with the given name.
void Database::addColumn(const std::string& tableName, const std::string& type)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->addColumn(type);
}


/// Update the values in the table with the given name where the value in the search column 
/// matches the provided search value. Update the target column with the target value.
void Database::update(const std::string& tableName, size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->update(searchColumnIndex, searchValue, targetColumnIndex, targetValue);
}


/// Remove rows from the table with the given name where the value in the specified column matches the provided value.
void Database::remove(const std::string& tableName, size_t columnIndex, const std::string& value)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->remove(columnIndex, value);
}


/// Insert a new row with the provided values into the table with the given name.
void Database::insert(const std::string& tableName, const std::vector<std::string>& values)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->insert(values);
}


/// Check if a table with the given name exists in the database.
bool Database::contains(const std::string& name)
{
	for (const auto& table : tables)
	{
		if (table->getName() == name)
			return true;
	}
	return false;
}


/// Get a pointer to the table with the given name from the database.
Table* Database::wantedTable(const std::string& tableName)
{
	for (const auto& table : tables)
	{
		if (table->getName() == tableName)
			return table;
	}
	return nullptr;
}

/// Clear the database by deleting all tables and freeing the associated memory.
void Database::clear()
{
	for (auto& table : tables)
		delete table; // Delete all tables in the database
}


/// Check if a file with the given filename exists.
bool Database::fileExists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}


/// Create a new file with the given filename.
void Database::createFile(const std::string& filename)
{
	std::ofstream file(filename);
	if (file.is_open())
		file.close();
	else
		throw std::exception("failed to create file"); // Throw an exception if the file creation fails
}
