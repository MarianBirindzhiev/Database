#pragma once
#include "Table.h"

class Database
{

public:

	Database(const std::string& fileName)
	{
		if (!isStringCorrect(fileName))
			throw std::exception("the given fileName is incorrect");

		this->fileName = fileName;
		setData();
	}

	~Database()
	{
		clear();
	}

	void setData()
	{
		std::ifstream file(this->fileName);
		if (!file)
			throw std::exception("could not open the file");

		std::string line;
		while (std::getline(file, line))
			import(line);
		
	}

	void saveData()
	{
		std::ofstream file(this->fileName);
		if (!file)
			throw std::exception("could not open the file");

		for (const auto& table : tables)
			file << table->getFileName() << '\n';
	}

	void showTables()
	{
		for (const auto& table : tables)
			std::cout << table->getName() << ' ';
	}

	void import(const std::string& fileName)
	{
		std::size_t dotPos = fileName.find('.');
		std::string tableName;

		if (dotPos != std::string::npos)
			tableName = fileName.substr(0, dotPos);
		else
			throw std::exception("invalid fileName format");
		
		if (contains(tableName))
			throw std::exception("There is already a table with that name in the database");

		Table* table = new Table(tableName, fileName);
		tables.push_back(table);
	}

	void print(const std::string& tableName)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->print();
	}

	void describe(const std::string& tableName)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->describe();
	}

	void saveTable(const std::string& tableName, const std::string& fileName)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->setFileName(fileName);
		wantedTable(tableName)->saveInFile();
	}

	void select(size_t columnIndex, const std::string& value, const std::string& tableName)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->select(columnIndex, value);
	}

	void select_onto(const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value, const std::string& tableName)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		tables.push_back(wantedTable(tableName)->select_onto(columnIndexes, columnIndex, value));
	}

	void addColumn(const std::string& tableName, const std::string& type)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->addColumn(type);
	}

	void update(const std::string& tableName,size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->update(searchColumnIndex, searchValue, targetColumnIndex, targetValue);
	}

	void remove(const std::string& tableName, size_t columnIndex, const std::string& value)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->remove(columnIndex, value);
	}

	void insert(const std::string& tableName, const std::vector<std::string>& values)
	{
		if (!contains(tableName))
			throw std::exception("There is not a table with that name in the database");

		wantedTable(tableName)->insert(values);
	}



private:

	std::vector<Table*> tables;
	std::string fileName;

	bool isStringCorrect(const std::string& name) { return name != ""; }

	bool contains(const std::string& name)
	{
		for (const auto& table : tables)
		{
			if (table->getName() == name)
				return true;
		}
		return false;
	}

	Table* wantedTable(const std::string& tableName)
	{
		for (const auto& table : tables)
		{
			if (table->getName() == tableName)
				return table;
		}
	}

	void clear()
	{
		for (auto& table : tables)
			delete table;
	}


};