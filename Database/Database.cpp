#include "Database.h"

Database::Database(const std::string& fileName)
{
	setFileName(fileName);
	setData();
}


Database::~Database()
{
	clear();
}


void Database::setData()
{
	if (!fileExists(this->fileName))
		createFile(this->fileName);

	std::ifstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file");

	std::string line;
	while (std::getline(file, line))
		import(line);

	file.close();

}


void Database::setFileName(const std::string& fileName)
{
	if (!isStringCorrect(fileName))
		throw std::exception("the given file name is invalid");

	this->fileName = fileName;
}


void Database::saveData()
{
	std::ofstream file(this->fileName);
	if (!file)
		throw std::exception("could not open the file");

	for (const auto& table : tables)
		file << table->getFileName() << '\n';

	file.close();
}


void Database::showTables()
{
	for (const auto& table : tables)
		std::cout << table->getName() << ' ';

	std::cout << '\n';
}


void Database::import(const std::string& fileName)
{
	std::size_t dotPos = fileName.find('.');
	std::string tableName;

	if (dotPos != std::string::npos)
		tableName = fileName.substr(0, dotPos);
	else
		throw std::exception("invalid fileName format");

	if (contains(tableName))
		throw std::exception("There is already a table with that name in the database");

	try
	{
		Table* table = new Table(tableName, fileName);
		tables.push_back(table);
	}
	catch (const std::bad_alloc& e)
	{
		std::cerr << "Failed to allocate memory: " << e.what() << '\n';
		clear();
	}
}


void Database::print(const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->print();
}


void Database::describe(const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->describe();
}


void Database::saveTable(const std::string& tableName, const std::string& fileName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->setFileName(fileName);
	wantedTable(tableName)->saveInFile();
}


void Database::select(size_t columnIndex, const std::string& value, const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->select(columnIndex, value);
}


void Database::select_onto(const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value, const std::string& tableName)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	tables.push_back(wantedTable(tableName)->select_onto(columnIndexes, columnIndex, value));
}


void Database::addColumn(const std::string& tableName, const std::string& type)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->addColumn(type);
}


void Database::update(const std::string& tableName, size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->update(searchColumnIndex, searchValue, targetColumnIndex, targetValue);
}


void Database::remove(const std::string& tableName, size_t columnIndex, const std::string& value)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->remove(columnIndex, value);
}


void Database::insert(const std::string& tableName, const std::vector<std::string>& values)
{
	if (!contains(tableName))
		throw std::exception("There is not a table with that name in the database");

	wantedTable(tableName)->insert(values);
}


bool Database::contains(const std::string& name)
{
	for (const auto& table : tables)
	{
		if (table->getName() == name)
			return true;
	}
	return false;
}


Table* Database::wantedTable(const std::string& tableName)
{
	for (const auto& table : tables)
	{
		if (table->getName() == tableName)
			return table;
	}
	return nullptr;
}


void Database::clear()
{
	for (auto& table : tables)
		delete table;
}


bool Database::fileExists(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}


void Database::createFile(const std::string& filename)
{
	std::ofstream file(filename);
	if (file.is_open())
		file.close();
	else
		throw std::exception("failed to create file");
}
