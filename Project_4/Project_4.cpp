// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"
#include <iostream>
#include <vector>

class graph_node
{
public:
	int dest;
	int weight;
	graph_node()
	{
		int dest = weight = 0;
	}
	graph_node(int dest, int weight)
	{
		this->dest = dest;
		this->weight = weight;
	}
};

void addEdge(Dictionary<int, LinkedList<graph_node>>& adj, int source, int dest, int weight)
{
	graph_node node(dest, weight);
	LinkedList<graph_node>* f_result;
	if (adj.Find(source, f_result))
	{
		(*f_result).push_back(node);
	}
	else
	{
		LinkedList<graph_node> value;
		value.push_back(node);
		adj.Insert(source, value);
	}

	//if (adj.Find(dest, f_result))
	//{
	//	(*f_result).push_back(source);
	//}
	//else
	//{
	//	LinkedList<int> value;
	//	value.push_back(source);
	//	adj.Insert(dest, value);
	//}
}

void printGraph(Dictionary<int, LinkedList<graph_node>> adj, int V)
{
	for (int v = 0; v < V; ++v)
	{
		cout << "\n Adjacency list of vertex "
			<< v << "\n head ";

		LinkedList<graph_node>* f_result;
		if (adj.Find(v, f_result))
		{
			auto iterator = f_result->create_list_iterator();
			while (iterator->has_next())
			{
				cout << "-> " << iterator->next().dest;
			}
		}
		printf("\n");
	}
}
int main()
{
	setlocale(LC_ALL, "Russian");
	int V = 5;
	Dictionary<int, LinkedList<graph_node>> adj;
	addEdge(adj, 0, 1, 1);
	addEdge(adj, 0, 4, 1);
	addEdge(adj, 1, 2, 1);
	addEdge(adj, 1, 3, 1);
	addEdge(adj, 1, 4, 1);
	addEdge(adj, 2, 3, 1);
	addEdge(adj, 3, 4, 1);
	printGraph(adj, V);
	return 0;
}