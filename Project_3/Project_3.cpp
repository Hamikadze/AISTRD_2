// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Project_2/RedBlackTree.cpp"

static bool count_compare(const void* elem1, const void* elem2)
{
	auto a = (Node<wchar_t, wstring>*)(elem1);
	auto b = (Node<wchar_t, wstring>*)elem2;
	return (a->get_count() /*<=*/ > b->get_count());
}

void ShannonCodes(Dictionary<wchar_t, wstring>& letters, LinkedList<Node<wchar_t, std::wstring>*>& nodes, int lenght, int left_index, int right_index)
{
	if (left_index == right_index)
	{
		return;
	}
	if (right_index - left_index == 1)
	{
		//  If interval consist of 2 elements then it's simple
		//
		letters.Find(nodes.at(left_index)->get_key())->append(L"0");
		letters.Find(nodes.at(right_index)->get_key())->append(L"1");
	}
	else
	{
		//  Calculating sum of probabilities at specified interval
		//
		float p_full = 0;
		for (int i = left_index; i <= right_index; ++i)
		{
			p_full += nodes.at(i)->get_count() / static_cast<float>(lenght);
		}

		//  Searching center
		//
		float p = 0;
		int split_index = -1; // index of split pos
		const float p_half = p_full * 0.5f;
		for (int i = left_index; i <= right_index; ++i)
		{
			p += nodes.at(i)->get_count() / static_cast<float>(lenght);
			if (p <= p_half) {
				letters.Find(nodes.at(i)->get_key())->append(L"0");
			}
			else
			{
				letters.Find(nodes.at(i)->get_key())->append(L"1");
				if (split_index < 0) split_index = i;
			}
		}

		if (split_index < 0) split_index = left_index + 1;

		//  Next step (recursive)
		//
		ShannonCodes(letters, nodes, lenght, left_index, split_index - 1);
		ShannonCodes(letters, nodes, lenght, split_index, right_index);
	}
}

std::wstring Encode(std::wstring & input, Dictionary<wchar_t, wstring> & table)
{
	std::wstring output;
	for (wchar_t letter : input)
	{
		output.append(*table.Find(letter));
	}
	return output;
}

std::wstring Decode(std::wstring input, Dictionary<wchar_t, wstring> & table)
{
	std::wstring output;
	while (input.length() > 0)
	{
		auto iterator = table.Nodes().create_list_iterator();
		while (iterator->has_next())
		{
			auto code = iterator->next();
			unsigned int code_length = code->get_value().length();
			if (input.compare(0, code_length, code->get_value()) == 0)
			{
				output += code->get_key();
				input = input.substr(code_length);
			};
		}
	};
	return output;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::wstring test_string = L"гигабайт";
	Dictionary<wchar_t, wstring> letters;
	for (wchar_t letter : test_string)
	{
		letters.Insert(letter, L"");
	}
	auto nodes = letters.Nodes();
	nodes.sort(count_compare);
	ShannonCodes(letters, nodes, test_string.length(), 0, letters.get_size() - 1);
	auto encode_str = Encode(test_string, letters);
	auto decode_str = Decode(encode_str, letters);
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