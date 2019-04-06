#pragma once
#include <iostream>
#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"

class ShennonFano
{
	LinkedList<Node<wchar_t, std::wstring>*> nodes;
	void ShannonCodes(Dictionary<wchar_t, wstring>& table, LinkedList<Node<wchar_t, std::wstring>*>& nodes, int lenght, int left_index, int right_index);

	static bool count_compare(Node<wchar_t, wstring>* elem1, Node<wchar_t, wstring>* elem2)
	{
		// ReSharper disable once CppCStyleCast
		auto a = (Node<wchar_t, wstring>*)(elem1);
		// ReSharper disable once CppCStyleCast
		auto b = (Node<wchar_t, wstring>*)(elem2);
		return (a->get_count() /*<=*/ > b->get_count());
	}
public:
	Dictionary<wchar_t, wstring> get_table(std::wstring input);
	std::wstring encode(std::wstring& input, Dictionary<wchar_t, wstring>& table);
	std::wstring decode(std::wstring input, Dictionary<wchar_t, wstring>& table);
	ShennonFano()
	{
		nodes.clear();
	};
	~ShennonFano()
	{
		nodes.clear();
	};
};
