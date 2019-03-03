// Project_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include<ctime>
#include "RedBlackTree.h"

using namespace std;

void test_int() {
	Tree<int, int> Dictionary;

	Dictionary.Insert(7, 3);
	Dictionary.Insert(2, 8);
	Dictionary.Insert(1, 9);
	Dictionary.Insert(3, 7);
	Dictionary.Insert(4, 6);
	Dictionary.Insert(9, 1);
	Dictionary.Insert(8, 2);

	if (Dictionary.Contains(9))
		cout << " test 1" << endl;
	Dictionary.Remove(9);
	if (!Dictionary.Contains(9))
		cout << " test 2" << endl;
	if (Dictionary.Find(9) == 1)
		cout << " test e" << endl;
	if (Dictionary.Find(8) == 2)
		cout << " test 3" << endl;
	cout << endl;
	auto list_keys = Dictionary.Keys().create_list_iterator();
	auto list_values = Dictionary.Values().create_list_iterator();
	while (list_keys->has_next() && list_values->has_next())
	{
		cout << list_keys->next() << " " << list_values->next() << endl;
	}
}

int main() {
	test_int();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file