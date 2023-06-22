#pragma once
#include "FloatColumn.h"
#include "IntColumn.h"
#include "StringColumn.h"


class Factory
{
public:

	static Factory& getFactory();

	Column* createColumn(const std::string& type);

private:
	Factory(){}
	~Factory(){}
	Factory(const Factory&) = delete;
	Factory& operator=(const Factory&) = delete;
};
