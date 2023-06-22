#pragma once
#include "Column.h"

class IntColumn : public Column
{
public:

	IntColumn() = default;

	IntColumn(const std::vector<int>& data)
		:data(data) {}

	~IntColumn() override = default;

	//Overrides the getType method and returns int
	std::string getType() const override { return "int"; }

	Column* clone() const override { return new IntColumn(*this); }

	void removeDataAtIndex(size_t index) override;

	//Returns true if the cell is empty
	bool isCellEmpty(size_t index) const override { return data.size() <= index || data[index] == 0; }

	std::string printDataAtIndex(size_t index) const override;

	//Returns the size
	size_t getSize() const override { return data.size(); }

	void addElement(const std::string& element) override;

	void update(const std::string& element, size_t index) override;

private:

	std::vector<int> data;
};