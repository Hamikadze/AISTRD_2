#pragma once

#include "FordFulkerson.h"

template <class T>
bool FordFulkerson<T>::edge_exist(T node1, T node2)
{
	return get_edge(node1, node2);
}

template <class T>
int FordFulkerson<T>::get_edge(T node1, T node2)
{
	LinkedList<EdgeNode<T>*>** f_value;
	int weight = 0;
	if (edges.Find(node1, f_value))
	{
		auto iterator = (*f_value)->create_list_iterator();
		while (iterator->has_next())
		{
			auto value = iterator->next();
			if (value->key == node2)
			{
				weight = value->weight;
				break;
			}
		}
	}
	return weight;
}

template <class T>
void FordFulkerson<T>::flow_change(T node1, T node2, int flow_change)
{
	LinkedList<EdgeNode<T>*>** f_value;
	if (edges.Find(node1, f_value))
	{
		auto iterator = (*f_value)->create_list_iterator();
		while (iterator->has_next())
		{
			auto value = iterator->next();
			if (value->key == node2)
			{
				value->weight = value->weight + flow_change;
			}
		}
	}
}

template <class T>
bool FordFulkerson<T>::read()
{
	std::ifstream file("Read.txt");
	std::string str;
	while (std::getline(file, str))
	{
		try {
			int city_from, city_to, price_to;
			std::istringstream iss(str);
			iss >> city_from >> city_to >> price_to;
			/*if (city_from.empty() || city_to.empty() || price_to.empty())
			{
				throw std::invalid_argument("Input data reading error");
			}
			if (is_u_int(price_to))
			{*/
			this->insert_edge(city_from, city_to, price_to);
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
bool FordFulkerson<T>::bfs(int s, int t, Dictionary<int, int>& parent)
{
	LinkedList<int> visited;
	LinkedList<T> q;
	q.push_back(s);
	visited.push_front(s);
	parent.Insert(s, -1);
	while (!q.isEmpty())
	{
		T u = q.at(0);
		q.pop_front();
		LinkedList<EdgeNode<T>*>** f_value;
		if (edges.Find(u, f_value)) {
			auto iterator = (*f_value)->create_list_iterator();
			while (iterator->has_next())
			{
				auto v = iterator->next()->key;
				if (!visited.contains(v) && edge_exist(u, v))
				{
					q.push_back(v);
					parent.Insert(v, u);
					visited.push_front(v);
				}
			}
		}
	}

	return visited.contains(t);
}
template <class T>
int FordFulkerson<T>::fordFulkerson(int s, int t)
{
	Dictionary<int, int> parent;

	int max_flow = 0;

	while (bfs(s, t, parent))
	{
		int path_flow = INT_MAX;
		LinkedList<int>vec;
		for (int v = t; v != s; v = parent.Find(v))
		{
			int u = parent.Find(v);
			path_flow = min(path_flow, get_edge(u, v));
			vec.push_back(v);
			flow_change(u, v, -1 * path_flow);
			flow_change(v, u, path_flow);
		}
		vec.push_back(s);
		for (int k = vec.get_size() - 1; k >= 0; k--)
			cout << vec.at(k) << "->";
		cout << " : " << path_flow << endl;
		max_flow += path_flow;
	}
	//rGraph->print();
	return max_flow;
}