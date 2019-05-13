#include "Graph.h"
#include <fstream>
#include <string>
#include <sstream>

template<class T>
void Graph<T>::insert_edge(T from, T to, int weight) {
	auto n = this->edges.FindOrInsert(from, new LinkedList<EdgeNode<T>*>());
	auto m = new EdgeNode<T>(to, weight);
	n->push_front(m);
}

template <class T>
bool Graph<T>::edge_exist(T, T)
{
	return get_edge(node1, node2);
}

template <class T>
int Graph<T>::get_edge(T, T)
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
void Graph<T>::flow_change(T, T, int)
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

template<class T>
void Graph<T>::print() {
	auto nodes = this->edges.Nodes();
	auto node_iterator = nodes.create_list_iterator();
	while (node_iterator->has_next())
	{
		auto node = node_iterator->next();
		cout << "Vertex " << node->get_key() << " has neighbors: " << endl;
		auto iterator = node->get_value()->create_list_iterator();
		while (iterator->has_next()) {
			auto node1 = iterator->next();
			cout << node1->key << " (" << node1->weight << ")" << endl;
		}
	}
}