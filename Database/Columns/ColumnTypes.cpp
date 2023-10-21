#include "FloatColumn.h"
#include "IntColumn.h"
#include "StringColumn.h"

const std::string nullObject = "NULL";

//Removes data at the specified index from the FloatColumn object.
///The data vector is searched for the specified index, and if found, the element at that index is erased from the vector.
///If the index is out of range, no action is taken.
void FloatColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}

//Removes data at the specified index from the IntColumn object.
///The data vector is searched for the specified index, and if found, the element at that index is erased from the vector.
///If the index is out of range, no action is taken.
void IntColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}
//Removes data at the specified index from the StringColumn object.
///The data vector is searched for the specified index, and if found, the element at that index is erased from the vector.
///If the index is out of range, no action is taken.
void StringColumn::removeDataAtIndex(size_t index)
{
	for (size_t i = 0; i < data.size(); i++)
	{
		if (index == i)
			data.erase(data.begin() + i);
	}
}


///Retrieves the data at the specified index from the FloatColumn object and returns it as a string.
/// If the cell at the specified index is empty, "NULL" is returned.
/// Otherwise, the float value at the specified index is converted to a string and returned.
std::string FloatColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? nullObject : std::to_string(data[index]);
}

///Retrieves the data at the specified index from the IntColumn object and returns it as a string.
/// If the cell at the specified index is empty, "NULL" is returned.
/// Otherwise, the float value at the specified index is converted to a string and returned.
std::string IntColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? nullObject : std::to_string(data[index]);
}

///Retrieves the data at the specified index from the StringColumn object and returns it as a string.
/// If the cell at the specified index is empty, "NULL" is returned.
/// Otherwise, the float value at the specified index is converted to a string and returned.
std::string StringColumn::printDataAtIndex(size_t index) const
{
	return isCellEmpty(index) ? nullObject : data[index];
}



///Adds a new element to the FloatColumn object.
///- element: The string representation of the element to add.
///  - If the element is "NULL", a default value of 0.00 is added to the data vector.
///  - Otherwise, the string is converted to a float value using std::stof() and added to the data vector.
void FloatColumn::addElement(const std::string& element)
{
	if (element == nullObject)
		data.push_back(0.00);
	else
		data.push_back(std::stof(element));
}

///Adds a new element to the IntColumn object.
///- element: The string representation of the element to add.
///  - If the element is "NULL", a default value of 0.00 is added to the data vector.
///  - Otherwise, the string is converted to a float value using std::stof() and added to the data vector.
void IntColumn::addElement(const std::string& element)
{
	if (element == nullObject)
		data.push_back(0);
	else
		data.push_back(std::stoi(element));
}

///Adds a new element to the StringColumn object.
///- element: The string representation of the element to add.
///  - If the element is "NULL", a default value of 0.00 is added to the data vector.
///  - Otherwise, the string is converted to a float value using std::stof() and added to the data vector.
void StringColumn::addElement(const std::string& element)
{
	if (element == nullObject)
		data.push_back("");
	else
		data.push_back(element);
}



///Updates the data at the specified index in the FloatColumn object with the given element.
///- element: The new value to update the cell with, provided as a string.
///  - The string is converted to a float value using std::stof() before updating the data vector.
/// - index: The index of the cell to update.
void FloatColumn::update(const std::string& element, size_t index)
{
	data[index] = std::stof(element);
}

///Updates the data at the specified index in the IntColumn object with the given element.
///- element: The new value to update the cell with, provided as a string.
///  - The string is converted to a float value using std::stof() before updating the data vector.
/// - index: The index of the cell to update.
void IntColumn::update(const std::string& element, size_t index) 
{
	data[index] = std::stoi(element);
}

///Updates the data at the specified index in the StringColumn object with the given element.
///- element: The new value to update the cell with, provided as a string.
///  - The string is converted to a float value using std::stof() before updating the data vector.
/// - index: The index of the cell to update.
void StringColumn::update(const std::string& element, size_t index) 
{
	data[index] = element;
}