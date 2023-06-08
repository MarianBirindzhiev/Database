#include <iostream>
#include <vector>
#include <string>
#include "Table.h"
#include "IntColumn.h"
#include "StringColumn.h"
#include "FloatColumn.h"



int main()
{
	IntColumn* col1 = new IntColumn{ {13414551,2,33,4,3125} };
	StringColumn* col2 = new StringColumn{ {"ivanaaaaaaaaaaaaaaaaaaa","petkab"} };
	FloatColumn* col3 = new FloatColumn{ {1.222,5.213,8.144,12.1323,-1223.2121, 1234.2222} };
	Table table("tablica1");

	col1->addElement("12");
	col3->addElement("312455.22123");

	table.addColumn(col1);
	table.addColumn(col3);
	table.addColumn(col2);

	table.print();
	table.describe();
}


