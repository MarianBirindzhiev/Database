#include <iostream>
#include <vector>
#include <string>
#include "Table.h"
#include "IntColumn.h"
#include "StringColumn.h"
#include "FloatColumn.h"
#include "Factory.h"
#include <fstream>
#include <sstream>


int main()
{
	IntColumn* col1 = new IntColumn{ {3,2,3,3,3125,} };
	//StringColumn* col2 = new StringColumn{ {"ivanaaaaaaaaaaaaaaaaaaa","petkab"} };
	//FloatColumn* col3 = new FloatColumn{ {1.222,5.213,8.144,12.1323,-1223.2121, 1234.2222} };
	//Table table("tablica1","test.txt");

	//IntColumn* col4 = new IntColumn;
	//col4->addElement(std::to_string(12));
	//col4->addElement("55");


	//col1->addElement("12");
	//col3->addElement("312455.22123");

	//col4->removeDataAtIndex(0);
	//col2->removeDataAtIndex(4);

	//table.addColumn(col1);
	//table.addColumn(col3);
	//table.addColumn(col2);
	//table.addColumn(col4);
	//table.describe();
	//table.print();

	//table.setColumnTypes();

	//std::cout << '\n';
	//table.describe();
	//table.print();
	//table.saveInFile();

	Table table("tablica1","test.txt");
	table.setData();
	table.describe();
	table.print();
	table.addColumn(col1);
	//table.saveInFile();
	std::cout << '\n';
	table.print();
	std::cout << '\n';
	table.select(7, "3");
	table.remove(6, "3125");
	std::cout << '\n';
	table.print();
	//table.saveInFile();

}


