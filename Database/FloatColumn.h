#pragma once
#include "Column.h"

class FloatColumn : public Column
{
public:

	FloatColumn() = default;

	FloatColumn(const std::vector<float>& data)
		:data(data) {}

	~FloatColumn() override = default;

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

	bool isCellEmpty(size_t index) const override { return data.size() <= index || data[index] == 0.00; }

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
			data.push_back(0.00);
		else
			data.push_back(std::stof(element));
	}

	void update(const std::string& element, size_t index) override
	{
		data[index] = std::stof(element);
	}

private:

	std::vector<float> data;
};
