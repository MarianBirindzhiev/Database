#pragma once
#include "../Table/Table.h"

class Database
{

public:

	Database(const std::string& fileName);

	Database(const Database& other);

	Database& operator=(const Database& other);

	~Database();

	void setData();

	void setFileName(const std::string& fileName);

	void saveData();

	void showTables();

	void import(const std::string& fileName);

	void print(const std::string& tableName);

	void describe(const std::string& tableName);

	void saveTable(const std::string& tableName, const std::string& fileName);

	void select(size_t columnIndex, const std::string& value, const std::string& tableName);

	void select_onto(const std::string& name, const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value, const std::string& tableName);

	void addColumn(const std::string& tableName, const std::string& type);

	void update(const std::string& tableName, size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue);

	void remove(const std::string& tableName, size_t columnIndex, const std::string& value);

	void insert(const std::string& tableName, const std::vector<std::string>& values);

	Table* wantedTable(const std::string& tableName);

private:

	std::vector<Table*> tables;
	std::string fileName;

	bool isStringCorrect(const std::string& name) { return name != ""; }

	bool contains(const std::string& name);

	void clear();

	bool fileExists(const std::string& filename);

	void createFile(const std::string& filename);
};