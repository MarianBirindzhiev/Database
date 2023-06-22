﻿#pragma once
#include "Column.h"

class StringColumn : public Column
{
public:

	StringColumn() = default;

	StringColumn(const std::vector<std::string>& data)
		:data(data) {}

	~StringColumn() override = default;

	//Overrides the getType method and returns string
	std::string getType() const override { return "string"; }

	Column* clone() const override { return new StringColumn(*this); }

	void removeDataAtIndex(size_t index) override;

	//Returns true if the cell is empty
	bool isCellEmpty(size_t index) const override { return data.size() <= index || data[index] == ""; }

	std::string printDataAtIndex(size_t index) const override;

	//Returns the size
	size_t getSize() const override { return data.size(); }

	void addElement(const std::string& element) override;

	void update(const std::string& element, size_t index) override;

private:

	std::vector<std::string> data;
};
