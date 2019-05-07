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