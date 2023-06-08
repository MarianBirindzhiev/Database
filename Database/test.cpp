#include <iostream>
#include <vector>
#include <string>
#include "Table.h"
#include "IntColumn.h"
#include "StringColumn.h"
#include "FloatColumn.h"
#include <iomanip>
int main()
{
	IntColumn* col1 = new IntColumn{ {13414551,2,33,4,3125} };
	StringColumn* col2 = new StringColumn{ {"ivanaaaaaaaaaaaaaaaaaaa","petkab"} };
	FloatColumn* col3 = new FloatColumn{ {1.2,5.2,8.1,12.3,-1223.2121, 1234.2222} };
	Table table;

	table.addColumn(col1);
	table.addColumn(col3);
	table.addColumn(col2);

	table.print();
}


