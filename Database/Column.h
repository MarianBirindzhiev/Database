#pragma once
#include <string>
#include <vector>
#include<iostream>
#include <iomanip>

class Column
{
public:

	virtual ~Column() {}

	virtual std::string getType() const = 0;
	virtual Column* clone() const = 0;
	virtual void removeDataAtIndex(size_t index) = 0;
	virtual bool isCellEmpty(size_t index) const = 0;

	virtual std::string printDataAtIndex(size_t index) const = 0;
	virtual size_t getSize() const = 0;
	virtual void addElement(const std::string& element) = 0;



};