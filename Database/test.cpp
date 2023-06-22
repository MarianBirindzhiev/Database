#include "Database.h"

int main()
{
	try
	{
		std::string command;
		std::string filename;
		std::string tableName;
		std::string value;
		int columnIndex;
		std::cout << "Enter the name of the file containing the database: ";
		std::cin >> command;

		Database base(command);

		while (command != "exit")
		{
			std::cout << "Enter a command: ";
			std::cin >> command;

			if (command == "import")
			{
				std::cout << "Enter the filename: ";
				std::cin >> filename;
				base.import(filename);
			}

			else if (command == "showtables")
			{
				base.showTables();
			}

			else if (command == "describe")
			{
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				base.describe(tableName);
			}

			else if (command == "print")
			{
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				base.print(tableName);
			}

			else if (command == "export")
			{
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				std::cout << "Enter the filename: ";
				std::cin >> filename;
				base.saveTable(tableName, filename);
			}

			else if (command == "select")
			{
				std::cout << "Enter the column index: ";
				std::cin >> columnIndex;
				std::cout << "Enter the value: ";
				std::cin >> value;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				base.select(columnIndex, value, tableName);
			}

			else if (command == "select_onto")
			{
				std::string resultTableName;
				std::vector<int> columns;
				int columnIndex;
				std::cout << "Enter the result table name: ";
				std::cin >> resultTableName;

				int numColumns;
				std::cout << "Enter the columns: ";
				std::cin >> numColumns;
				std::cout << "Enter the data: \n";
				for (int i = 0; i < numColumns; ++i) 
				{
					int columnIndex;
					std::cin >> columnIndex;
					columns.push_back(columnIndex);
				}

				std::cout << "Enter the column index: ";
				std::cin >> columnIndex;
				std::cout << "Enter the value: ";
				std::cin >> value;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				base.select_onto(resultTableName, columns, columnIndex, value, tableName);
			}

			else if (command == "addColumn")
			{
				std::string columnType;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				std::cout << "Enter the column type: ";
				std::cin >> columnType;
				base.addColumn(tableName, columnType);
			}

			else if (command == "update")
			{
				std::string tableName, searchValue, targetColumnValue;
				int searchColumnIndex, targetColumnIndex;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				std::cout << "Enter the search column index: ";
				std::cin >> searchColumnIndex;
				std::cout << "Enter the search value: ";
				std::cin >> searchValue;
				std::cout << "Enter the target column index: ";
				std::cin >> targetColumnIndex;
				std::cout << "Enter the target column value: ";
				std::cin >> targetColumnValue;
				base.update(tableName, searchColumnIndex, searchValue, targetColumnIndex, targetColumnValue);
			}

			else if (command == "delete") 
			{
				std::string tableName, searchValue;
				int searchColumnIndex;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				std::cout << "Enter the search column index: ";
				std::cin >> searchColumnIndex;
				std::cout << "Enter the search value: ";
				std::cin >> searchValue;
				base.remove(tableName, searchColumnIndex, searchValue);
			}

			else if (command == "insert")
			{
				std::string tableName;
				std::vector<std::string> values;
				std::cout << "Enter the table name: ";
				std::cin >> tableName;
				std::cout << "Enter the data: \n";
				for (int i = 0; i < base.wantedTable(tableName)->getSize(); ++i)
				{
					std::string value;
					std::cin >>value ;
					values.push_back(value);
				}

				base.insert(tableName, values);
			}

			else if (command == "close")
			{
				base.saveData();
				break;
			}

			else if (command == "save")
			{
				base.saveData();
			}

			else if (command == "save_as")
			{
				std::cout << "Enter the filename: ";
				std::cin >> filename;

				base.setFileName(filename);
				base.saveData();
			}

			else
				std::cout << "Invalid command. Please try again.\n";
		}

	}
	catch (const std::exception& e)
	{
		std::cout << e.what()<<'\n';
	}


}


