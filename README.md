# Inventory-Management

This project consists of an inventory management system, coded in C++ using Visual Studios. 
A clothing store manager can use this software to create and delete stock items, sell stock items, manage stock level and check inventory. 
Each stock item contains its own unique attributes as well as identification.
The program has a command-line based user interface and is very intuitive to use.


The program architectures consist of several classes and multi-level inheritances/polymorphism. Each stock item is stored in an array of pointers. 
Exceptions are thrown when users inputs are invalid, or if other program error occurs. 
Catch blocks are implemented to handle these exceptions and print error messages. 
To improve debugging and code-analysis capabilities, the program consists of a header file, and two cpp source files. 
