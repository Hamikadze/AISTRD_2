#pragma once
#include <iostream>
#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"

class ShennonFano
{
private:
	LinkedList<Node<wchar_t, std::wstring>*> nodes;
	void ShannonCodes(Dictionary<wchar_t, wstring>& table, int left_index, int right_index);
	static bool count_compare(Node<wchar_t, wstring>* elem1, Node<wchar_t, wstring>* elem2)
	{
		return (elem1->get_count() > elem2->get_count());
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
