#pragma once
#include "Column.h"
#include "Factory.h"
#include <fstream>
#include <sstream>

class Table
{
public:
	Table(const std::string& name);

	Table(const std::string& name, const std::string& fileName);

	~Table();

	void print();
	
	void saveInFile();

	void addColumn(Column* col);

	void addColumn(const std::string& type);

	void describe();

	const std::string getName() const { return this->name; }

	const std::string getFileName() const { return this->fileName; }

	void setFileName(const std::string& fileName);

	void setData();

	void select(size_t columnIndex, const std::string& value);

	Table* select_onto(const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value);

	void remove(size_t columnIndex, const std::string& value);

	void update(size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue);

	void insert(const std::vector<std::string>& values);


private:

	std::string name;
	std::vector<Column*> dataTable;
	std::string fileName;

	void clear();

	bool isStringCorrect(const std::string& name) { return name != ""; }

	bool isColumnIndexCorrect(size_t index) { return index >= 0 && index < dataTable.size(); }

	size_t getMaxNumberRow();

	std::vector<size_t> columnWidth();

	std::vector<int> rowHelper(size_t columnIndex, const std::string& value);
};