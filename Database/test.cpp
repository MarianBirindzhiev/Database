#include "Database.h"

int main()
{
	try
	{
		Database base("DataBase.txt");
		base.print("table1");
		base.showTables();
		base.select(0, "2", "table1");

	}
	catch (const std::exception& e)
	{
		std::cout << e.what()<<'\n';
	}


}


