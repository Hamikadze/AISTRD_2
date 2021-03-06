#include "ShennonFano.h"
#include "math.h"

void ShennonFano::ShannonCodes(Dictionary<wchar_t, wstring>& table, int left_index, int right_index)
{
	if (left_index == right_index)
	{
		return;
	}
	if (right_index - left_index == 1)
	{
		/*  If interval consist of 2 elements then it's simple
		*/
		std::wstring* str;
		if (table.Find(nodes.at(left_index)->get_key(), str))
			str->append(L"0");
		if (table.Find(nodes.at(right_index)->get_key(), str))
			str->append(L"1");
	}
	else
	{
		/*  Calculating sum of probabilities at specified interval
		/*/
		float p_full = 0;
		for (int i = left_index; i <= right_index; ++i)
		{
			p_full += nodes.at(i)->get_count();
		}

		/*  Searching center
		/*/
		float p = 0; // p - probability
		int split_index = -1; // index of split pos
		const int p_half = round(p_full * 0.5f);
		for (int i = left_index; i <= right_index; ++i)
		{
			std::wstring* str;
			p += nodes.at(i)->get_count();
			//If the probability is less than the "average" or split index not found yet
			if (p <= p_half || split_index < 0) {
				split_index = i;
				//append zero to code
				if (table.Find(nodes.at(i)->get_key(), str))
					str->append(L"0");
			}
			else
			{
				//append 1 to code
				if (table.Find(nodes.at(i)->get_key(), str))
					str->append(L"1");
			}
		}

		/*  Next step (recursive)
		 *  Repeat the operation for the first and second half
		*/
		ShannonCodes(table, left_index, split_index);
		ShannonCodes(table, split_index + 1, right_index);
	}
}

std::wstring ShennonFano::encode(std::wstring& input, Dictionary<wchar_t, wstring>& table)
{
	std::wstring output;
	if (input.length() && table.get_size())
		//Just find the codes by key (letter) in the associative array
		for (wchar_t letter : input)
		{
			std::wstring* str;
			if (table.Find(letter, str))
				output.append(*str);
		}
	return output;
}

std::wstring ShennonFano::decode(std::wstring input, Dictionary<wchar_t, wstring>& table)
{
	std::wstring output = L"";
	while (input.length() && table.get_size())
	{
		auto iterator = table.Nodes().create_list_iterator();
		bool found = false;
		/*In the list of keys and values, we find matches of codes,
		 * if no match is found, we interrupt the search.*/
		while (iterator->has_next())
		{
			auto code = iterator->next();
			const unsigned int code_length = code->get_value().length();
			if (input.compare(0, code_length, code->get_value()) == 0)
			{
				output += code->get_key();
				input = input.substr(code_length);
				found = true;
			};
		}
		if (!found) break;
	};
	return output;
}

Dictionary<wchar_t, wstring> ShennonFano::get_table(std::wstring input)
{
	static Dictionary<wchar_t, wstring> letters;
	if (input.length()) {
		/*Just loop through the letters from the source string, insert it into the dictionary.
		 *When inserting an already existing key-value pair, the value is replaced,
		 *and the internal counter of such inserts increases (needed for frequency analysis)*/
		for (wchar_t letter : input)
		{
			letters.Insert(letter, L"");
		}
		nodes = letters.Nodes();
		//Sort the list in order of decreasing frequency
		nodes.sort(count_compare);
		ShannonCodes(letters, 0, letters.get_size() - 1);
	}
	return letters;
}