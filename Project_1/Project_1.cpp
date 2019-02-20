// Project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
//#include <iostream>
#include "LinkedList.h"
#include "LinkedList.cpp"

int main()
{
	std::cout << "Hello World!\n";
	LinkedList<int> list;
	list.push_back(4);
	list.push_back(1);
	list.push_back(5);
	list.push_back(7);
	list.push_back(13);

	LinkedList<int> check;
	check.push_back(5);
	check.push_back(5);
	check.push_back(7);
	check.push_back(13);

	std::cout << list.contains(&check) << std::endl;
	std::cout << list;// .print_to_console();

	system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu