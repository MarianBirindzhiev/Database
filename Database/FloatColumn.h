#pragma once
#include "Column.h"

class FloatColumn : public Column
{
public:

	FloatColumn() = default;

	FloatColumn(const std::vector<float>& data)
		:data(data) {}

	~FloatColumn() override = default;

	//Overrides the getType method and returns float
	std::string getType() const override { return "float"; }

	Column* clone() const override { return new FloatColumn(*this); }

	void removeDataAtIndex(size_t index) override;

	//Returns true if the cell is empty
	bool isCellEmpty(size_t index) const override { return data.size() <= index || data[index] == 0.00; }

	std::string printDataAtIndex(size_t index) const override;

	//Returns the size
	size_t getSize() const override { return data.size(); }

	void addElement(const std::string& element) override;

	void update(const std::string& element, size_t index) override;

private:

	std::vector<float> data;
};
