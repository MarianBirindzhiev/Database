#pragma once
#include "Column.h"

class StringColumn : public Column
{
public:

	StringColumn(const std::vector<std::string>& data)
		:data(data) {}

	std::string getType() const override { return "string"; }

	Column* clone() const override { return new StringColumn(*this); }

	void removeDataAtIndex(size_t index) override
	{
		for (size_t i = 0; i < data.size(); i++)
		{
			if (index == i)
				data.erase(data.begin() + i);
		}
	}
	bool isCellEmpty(size_t index) const override { return data.size() <= index; }

	std::string printDataAtIndex(size_t index) const override
	{
		return isCellEmpty(index) ? "null" : data[index];
	}

	size_t getSize() const override
	{
		return data.size();
	}

	void addElement(const std::string& element) override
	{
		data.push_back(element);
	}

private:

	std::vector<std::string> data;
};
