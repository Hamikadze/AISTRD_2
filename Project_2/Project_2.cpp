// Project_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "RedBlackTree.cpp"

using namespace std;
//
//void test_int() {
//	Dictionary<int, int> dictionary;
//
//	dictionary.Insert(7, 3);
//	dictionary.Insert(2, 8);
//	dictionary.Insert(1, 9);
//	dictionary.Insert(3, 7);
//	dictionary.Insert(4, 6);
//	dictionary.Insert(9, 1);
//	dictionary.Insert(8, 2);
//
//	if (dictionary.Contains(9))
//		cout << " test 1" << endl;
//	dictionary.Remove(9);
//	if (!dictionary.Contains(9))
//		cout << " test 2" << endl;
//	if (dictionary.Find(9) == 1)
//		cout << " test e" << endl;
//	if (dictionary.Find(8) == 2)
//		cout << " test 3" << endl;
//	cout << endl;
//	auto list_keys = dictionary.Keys().create_list_iterator();
//	auto list_values = dictionary.Values().create_list_iterator();
//	while (list_keys->has_next() && list_values->has_next())
//	{
//		cout << list_keys->next() << " " << list_values->next() << endl;
//	}
//
//	dictionary.Insert(4, 555);
//	list_keys = dictionary.Keys().create_list_iterator();
//	list_values = dictionary.Values().create_list_iterator();
//	while (list_keys->has_next() && list_values->has_next())
//	{
//		cout << list_keys->next() << " " << list_values->next() << endl;
//	}
//}

int main() {
	int data;
	Dictionary<int, int> rbTree1;

	rbTree1.Insert(1, 1);

	rbTree1.Insert(2, 2);

	rbTree1.Insert(3, 3);
	rbTree1.Insert(4, 4);
	rbTree1.Insert(5, 5);

	rbTree1.Remove(1);
	rbTree1.Remove(3);
	rbTree1.Remove(5);
	system("pause");
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