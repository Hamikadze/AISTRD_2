// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ShennonFano.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	std::wstring test_string = L"1234";
	std::wstring test_string2 = L"1234";
	ShennonFano shennon;
	auto table = shennon.get_table(test_string);
	auto n = table.Nodes();
	auto encode_str = shennon.encode(test_string2, table);
	auto decode_str = shennon.decode(encode_str, table);
	std::cout << "Hello World!\n";
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