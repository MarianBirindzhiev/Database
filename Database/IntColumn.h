#pragma once
#include "Column.h"

class IntColumn : public Column
{
public:

	IntColumn() = default;

	IntColumn(const std::vector<int>& data)
		:data(data) {}

	~IntColumn() override = default;

	std::string getType() const override { return "int"; }

	Column* clone() const override { return new IntColumn(*this); }

	void removeDataAtIndex(size_t index) override
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			if (index == i)
				data.erase(data.begin() + i);
		}
	}

	bool isCellEmpty(size_t index) const override { return data.size() <= index || data[index] == 0; }

	std::string printDataAtIndex(size_t index) const override
	{
		return isCellEmpty(index) ? "NULL" : std::to_string(data[index]);
	}

	size_t getSize() const override
	{
		return data.size();
	}

	void addElement(const std::string& element) override
	{
		if (element == "NULL")
			data.push_back(0);
		else
			data.push_back(std::stoi(element));
	}

	void update(const std::string& element, size_t index) override
	{
		data[index] = std::stoi(element);
	}

private:

	std::vector<int> data;
};