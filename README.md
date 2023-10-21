# Simple Database Operations Project

## Description

This project aims to implement an application that supports operations with simple databases. The databases consist of a series of tables, with each table saved in its own file. The database is stored in a main file (directory) containing a list of tables in the database, each with a name and the file in which the table is stored.

### Supported Data Types

Each column in a table within the database has a data type. The application supports the following data types:

- Integer: A series of digits, with an optional '+' or '-' sign at the beginning. Examples: 123, -123, +123.
- Floating-Point Number: A series of digits followed by a period and another series of digits, with an optional '+' or '-' sign at the beginning. Examples: 123.456, -123.456, +123.456.
- String: A sequence of arbitrary characters enclosed in double quotes. To include a double quote character in a string, escape it as \" (e.g., "Hello world!").
- Null: Represents an empty cell, denoted as "NULL."

## Features

The application supports various database operations, including:

1. `import <file name>`: Add a new table to the database from a file.
2. `showtables`: List all the tables in the database.
3. `describe <name>`: Display column type information for a specific table.
4. `print <name>`: Display all rows from a table in a paginated view.
5. `export <name> <file name>`: Save the content of a table to a text file.
6. `select <column-n> <value> <table name>`: Retrieve rows from a table based on a specific column value.
7. `select_onto <result_table> [<comumn_1>, <column_2>, ...] <column-n> <value> <table name>`: Similar to `select`, but results are stored in a new table.
8. `add_column <table name> <column name> <column type>`: Add a new column to a table.
9. `update <table name> <search column n> <search value> <target column n> <target value>`: Update rows in a table based on search criteria.
10. `delete <table name> <search column n> <search value>`: Delete rows from a table based on search criteria.
11. `insert <table name> <column 1> … <column n>`: Insert a new row into a table with specified values.
12. `save`: Save the changes made to the database.
13. `save_as <file name>`: Save the database with a different file name.
14. `close`: Save changes and exit the application.
15. `exit`: Exit the application without saving.

## Techonologies Used
- Programming Language: C++
- Doxygen
