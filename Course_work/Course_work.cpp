// Course_work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include "../Project_2/RedBlackTree.cpp"
#include "FordFulkerson.cpp"

using namespace std;

int main()
{
	auto g = new FordFulkerson<int>();
	if (g->read()) {
		g->print();
		cout << g->fordFulkerson(1, 4) << endl;
	}
	return 0;
}