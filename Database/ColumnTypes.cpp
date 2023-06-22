#include "Factory.h"

Factory& Factory::getFactory()
{
	static Factory theFactory;
	return theFactory;
}

Column* Factory::createColumn(const std::string& type)
{
	if (type == "int")
		return new IntColumn();
	if (type == "string")
		return new StringColumn();
	if (type == "float")
		return new FloatColumn();

	return nullptr;
}



void FloatColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}

void IntColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}

void StringColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}



std::string FloatColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? "NULL" : std::to_string(data[index]);
}

std::string IntColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? "NULL" : std::to_string(data[index]);
}

std::string StringColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? "NULL" : data[index];
}




void FloatColumn::addElement(const std::string& element)
{
	if (element == "NULL")
		data.push_back(0.00);
	else
		data.push_back(std::stof(element));
}

void IntColumn::addElement(const std::string& element)
{
	if (element == "NULL")
		data.push_back(0);
	else
		data.push_back(std::stoi(element));
}

void StringColumn::addElement(const std::string& element)
{
	if (element == "NULL")
		data.push_back("");
	else
		data.push_back(element);
}




void FloatColumn::update(const std::string& element, size_t index)
{
	data[index] = std::stof(element);
}

void IntColumn::update(const std::string& element, size_t index) 
{
	data[index] = std::stoi(element);
}

void StringColumn::update(const std::string& element, size_t index) 
{
	data[index] = element;
}