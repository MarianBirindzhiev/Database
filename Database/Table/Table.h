#pragma once
#include "../Columns/Column.h"
#include "../Factory/Factory.h"
#include <fstream>
#include <sstream>
#include <exception>

class Table
{
public:
	Table(const std::string& name);

	Table(const std::string& name, const std::string& fileName);

	Table(const Table& other);

	Table& operator=(const Table& other);

	~Table();

	void print();
	
	void saveInFile();

	void addColumn(Column* col);

	void addColumn(const std::string& type);

	void describe();

	/// Returns the name of the table
	const std::string getName() const { return this->name; }
	
	/// Returns the file name of the table
	const std::string getFileName() const { return this->fileName; }

	void setFileName(const std::string& fileName);

	void setData();

	void select(size_t columnIndex, const std::string& value);

	Table* clone() const {return new Table(*this);}

	Table* select_onto(const std::string& name, const std::vector<int>& columnIndexes, size_t columnIndex, const std::string& value);

	void remove(size_t columnIndex, const std::string& value);

	void update(size_t searchColumnIndex, const std::string& searchValue, size_t targetColumnIndex, const std::string& targetValue);

	void insert(const std::vector<std::string>& values);

	/// Returns the size of the table
	size_t getSize() { return dataTable.size(); }
private:

	std::string name;
	std::vector<Column*> dataTable;
	std::string fileName;

	void clear();

	bool isStringCorrect(const std::string& name) { return name != ""; }

	/// Returns true if the passed index is correct
	bool isColumnIndexCorrect(size_t index) { return index >= 0 && index < dataTable.size(); }

	size_t getMaxNumberRow();

	std::vector<size_t> columnWidth();

	std::vector<int> rowHelper(size_t columnIndex, const std::string& value);
};