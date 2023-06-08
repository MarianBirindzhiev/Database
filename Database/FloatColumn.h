#pragma once
#include "Column.h"

class FloatColumn : public Column
{
public:

	FloatColumn(const std::vector<float>& data)
		:data(data) {}

	std::string getType() const override { return "float"; }
	Column* clone() const override { return new FloatColumn(*this); }
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
		return isCellEmpty(index) ? "null" : std::to_string(data[index]);
	}
	size_t getSize() const override
	{
		return data.size();
	}

private:

	std::vector<float> data;
};
