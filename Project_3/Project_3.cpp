// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../Project_2/RedBlackTree.cpp"

static bool count_compare(const void* elem1, const void* elem2)
{
	auto a = (Node<char, string>*)(elem1);
	auto b = (Node<char, string>*)elem2;
	return (a->get_count() /*<=*/ > b->get_count());
}

void EncShannon(Dictionary<char, string>& letters, LinkedList<Node<char, std::string>*>& nodes, int lenght, int left_index, int right_index)
{
	if (left_index == right_index)
	{
		return;
	}
	if (right_index - left_index == 1)
	{
		//  If interval consist of 2 elements then it's simple
		//
		letters.Find(nodes.at(left_index)->get_key())->append("0");
		letters.Find(nodes.at(right_index)->get_key())->append("1");
	}
	else
	{
		//  Calculating sum of probabilities at specified interval
		//
		float pfull = 0;
		for (int i = left_index; i <= right_index; ++i)
		{
			pfull += nodes.at(i)->get_count() / (float)lenght;
		}

		//  Searching center
		//
		float p = 0;
		int isp = -1; // index of split pos
		float phalf = pfull * 0.5f;
		for (int i = left_index; i <= right_index; ++i)
		{
			p += nodes.at(i)->get_count() / (float)lenght;
			if (p <= phalf) {
				letters.Find(nodes.at(i)->get_key())->append("0");
			}
			else
			{
				letters.Find(nodes.at(i)->get_key())->append("1");
				if (isp < 0) isp = i;
			}
		}

		if (isp < 0) isp = left_index + 1;

		//  Next step (recursive)
		//
		EncShannon(letters, nodes, lenght, left_index, isp - 1);
		EncShannon(letters, nodes, lenght, isp, right_index);
	}
}

int main()
{
	std::string test_string = "aaaaaaaassbbbdddd";
	Dictionary<char, string> letters;
	for (char letter : test_string)
	{
		letters.Insert(letter, "");
	}
	auto nodes = letters.Nodes();
	nodes.sort(count_compare);
	EncShannon(letters, nodes, test_string.length(), 0, letters.get_size() - 1);

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