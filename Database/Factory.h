#pragma once
#include "FloatColumn.h"
#include "IntColumn.h"
#include "StringColumn.h"


class Factory
{
public:

	static Factory& getFactory()
	{
		static Factory theFactory;
		return theFactory;
	}

	Column* createColumn(const std::string& type)
	{
		if (type == "int")
			return new IntColumn();
		if (type == "string")
			return new StringColumn;
		if (type == "float")
			return new FloatColumn();

		return nullptr;
	}

private:
	Factory(){}
	~Factory(){}
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;
};
