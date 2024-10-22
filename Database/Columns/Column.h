#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <exception>

class Column
{
public:
	/// Virtual destructor
	virtual ~Column() {};

	/// Returns the type of the column
	virtual std::string getType() const = 0;

	/// Returns a clone of the column
	virtual Column* clone() const = 0;

	/// Removes data at passed index
	virtual void removeDataAtIndex(size_t index) = 0;

	/// Checks if a cell is empty
	virtual bool isCellEmpty(size_t index) const = 0;

	/// Returns the data at given index
	virtual std::string printDataAtIndex(size_t index) const = 0;

	/// Return the size of the column
	virtual size_t getSize() const = 0;

	/// Adds an element passed as a parametre
	virtual void addElement(const std::string& element) = 0;

	/// Updates an element at a given index
	virtual void update(const std::string& elememt,size_t index) = 0;



};