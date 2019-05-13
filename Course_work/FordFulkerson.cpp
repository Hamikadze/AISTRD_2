#pragma once

#include "FordFulkerson.h"

template <class T>
bool FordFulkerson<T>::read()
{
	std::ifstream file("Read.txt");
	std::string str;
	while (std::getline(file, str))
	{
		try {
			int from, to, weight;
			std::istringstream iss(str);
			iss >> from >> to >> weight;
			/*if (city_from.empty() || city_to.empty() || price_to.empty())
			{
				throw std::invalid_argument("Input data reading error");
			}
			if (is_u_int(price_to))
			{*/
			this->insert_edge(from, to, weight);
			//}
		}
		catch (std::invalid_argument & e)
		{
			continue;
		}
	}
	return true;
}

template <class T>
bool FordFulkerson<T>::bfs(int from, int to, Dictionary<int, int>& parent)
{
	LinkedList<int> visited;
	LinkedList<T> queue;
	queue.push_back(from);
	visited.push_front(from);
	parent.Insert(from, -1);
	while (!queue.isEmpty())
	{
		T u = queue.at(0);
		queue.pop_front();
		LinkedList<EdgeNode<T>*>** f_value;
		if (edges.Find(u, f_value)) {
			auto iterator = (*f_value)->create_list_iterator();
			while (iterator->has_next())
			{
				auto v = iterator->next()->key;
				if (!visited.contains(v) && edge_exist(u, v))
				{
					queue.push_back(v);
					parent.Insert(v, u);
					visited.push_front(v);
				}
			}
		}
	}

	return visited.contains(to);
}
template <class T>
int FordFulkerson<T>::fordFulkerson(int from, int to)
{
	Dictionary<int, int> parent;

	int max_flow = 0;

	while (bfs(from, to, parent))
	{
		int path_flow = INT_MAX;
		LinkedList<int>vec;
		for (int i = to; i != from; i = parent.Find(i))
		{
			int u = parent.Find(i);
			path_flow = min(path_flow, get_edge(u, i));
			vec.push_back(i);
			flow_change(u, i, -1 * path_flow);
			flow_change(i, u, path_flow);
		}
		vec.push_back(from);
		for (int i = vec.get_size() - 1; i >= 0; i--)
			cout << vec.at(i) << "->";
		cout << " : " << path_flow << endl;
		max_flow += path_flow;
	}
	return max_flow;
}