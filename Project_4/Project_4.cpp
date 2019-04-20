// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"
#include <iostream>
#include <vector>

void addEdge(Dictionary<int, LinkedList<int>>& adj, int u, int v)
{
	LinkedList<int>* f_result;
	if (adj.Find(u, f_result))
	{
		(*f_result).push_back(v);
	}
	else
	{
		LinkedList<int> value;
		value.push_back(v);
		adj.Insert(u, value);
	}

	if (adj.Find(v, f_result))
	{
		(*f_result).push_back(u);
	}
	else
	{
		LinkedList<int> value;
		value.push_back(u);
		adj.Insert(v, value);
	}
}

void printGraph(Dictionary<int, LinkedList<int>> adj, int V)
{
	for (int v = 0; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex "
			<< v << "\n head ";

		LinkedList<int>* f_result;
		if (adj.Find(v, f_result))
		{
			auto iterator = f_result->create_list_iterator();
			while (iterator->has_next())
			{
				cout << "-> " << iterator->next();
			}
		}
		printf("\n");
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int V = 5;
	Dictionary<int, LinkedList<int>> adj;
	addEdge(adj, 0, 1);
	addEdge(adj, 0, 4);
	addEdge(adj, 1, 2);
	addEdge(adj, 1, 3);
	addEdge(adj, 1, 4);
	addEdge(adj, 2, 3);
	addEdge(adj, 3, 4);
	printGraph(adj, V);
	return 0;
}