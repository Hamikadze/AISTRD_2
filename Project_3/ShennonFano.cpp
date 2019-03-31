#include "ShennonFano.h"

void ShennonFano::ShannonCodes(Dictionary<wchar_t, wstring>& table, LinkedList<Node<wchar_t, std::wstring>*>& nodes,
	int lenght, int left_index, int right_index)
{
	if (left_index == right_index)
	{
		return;
	}
	if (right_index - left_index == 1)
	{
		//  If interval consist of 2 elements then it's simple
		//
		table.Find(nodes.at(left_index)->get_key())->append(L"0");
		table.Find(nodes.at(right_index)->get_key())->append(L"1");
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
				table.Find(nodes.at(i)->get_key())->append(L"0");
			}
			else
			{
				table.Find(nodes.at(i)->get_key())->append(L"1");
				if (split_index < 0) split_index = i;
			}
		}

		if (split_index < 0) split_index = left_index + 1;

		//  Next step (recursive)
		//
		ShannonCodes(table, nodes, lenght, left_index, split_index - 1);
		ShannonCodes(table, nodes, lenght, split_index, right_index);
	}
}

std::wstring ShennonFano::encode(std::wstring & input, Dictionary<wchar_t, wstring> & table)
{
	std::wstring output;
	for (wchar_t letter : input)
	{
		output.append(*table.Find(letter));
	}
	return output;
}

std::wstring ShennonFano::decode(std::wstring input, Dictionary<wchar_t, wstring> & table)
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

Dictionary<wchar_t, wstring> ShennonFano::get_table(std::wstring input)
{
	static Dictionary<wchar_t, wstring> letters;
	for (wchar_t letter : input)
	{
		letters.Insert(letter, L"");
	}
	LinkedList<Node<wchar_t, std::wstring>*> nodes = letters.Nodes();
	nodes.sort(count_compare);
	ShannonCodes(letters, nodes, input.length(), 0, letters.get_size() - 1);
	return letters;
}