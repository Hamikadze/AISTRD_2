#include <iostream>
#include <limits>
#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"
using namespace std;

template<class T>
class EdgeNode {
public:
	T key;
	int weight;
	EdgeNode(T key, int weight) {
		this->key = key;
		this->weight = weight;
	};
	EdgeNode()
	{
		this->key = {};
		this->weight = 0;
	}
};

template<class T>
class Graph {
public:
	Dictionary<T, LinkedList<EdgeNode<T>*>*> edges;
	Graph();
	~Graph();
	void insert_edge(T, T, int);
	void print();
};

template<class T>
Graph<T>::Graph() {
	/*for (int i = 1; i < (MAXV + 1); i++) {
		this->edges[i] = nullptr;
	}*/
}

template<class T>
Graph<T>::~Graph() {
	//to do
}

template<class T>
void Graph<T>::insert_edge(T from, T to, int weight) {
	auto n = this->edges.FindOrInsert(from, new LinkedList<EdgeNode<T>*>());
	auto m = new EdgeNode<T>(to, weight);
	n->push_front(m);
}

template<class T>
void Graph<T>::print() {
	for (int v = 1; v < (10001); v++) {
		LinkedList<EdgeNode<T>*>** f_result;
		if (this->edges.Find(v, f_result)) {
			cout << "Vertex " << v << " has neighbors: " << endl;
			auto iterator = (*f_result)->create_list_iterator();
			while (iterator->has_next()) {
				auto node = iterator->next();
				cout << node->key << " (" << node->weight << ")" << endl;
			}
		}
	}
}

template<class T>
void dijkstra_shortest_path(Graph<T>* g, Dictionary<T, T>& parent, Dictionary<T, int>& distance, int start) {
	Dictionary<int, bool> discovered;

	distance.Insert(start, 0);
	T v_curr = start;

	while (!discovered.Find(v_curr)) {
		discovered.Insert(v_curr, true);
		LinkedList<EdgeNode<T>*>** curr_list;
		if (g->edges.Find(v_curr, curr_list)) {
			Iterator<EdgeNode<T>*>* iteartor = (*curr_list)->create_list_iterator();
			while (iteartor->has_next()) {
				EdgeNode<T>* curr = iteartor->next();
				T v_neighbor = curr->key;
				int weight = curr->weight;
				int max_value1 = std::numeric_limits<int>::max();
				int max_value2 = std::numeric_limits<int>::max();
				int* f_result_curr = &max_value1;
				int* f_result_naib = &max_value2;
				distance.Find(v_curr, f_result_curr);
				distance.Find(v_neighbor, f_result_naib);
				if (*f_result_curr + weight < *f_result_naib) {
					distance.Insert(v_neighbor, distance.Find(v_curr) + weight);
					parent.Insert(v_neighbor, v_curr);
				}
			}
		}
		//set the next current vertex to the vertex with the smallest distance
		int smallest_dist = std::numeric_limits<int>::max();
		auto iterator = distance.Nodes().create_list_iterator();
		auto iterator_disc = discovered.Values().create_list_iterator();
		while (iterator->has_next())
		{
			auto node = iterator->next();
			if (!discovered.Find(node->get_key()) && node->get_value() < smallest_dist) {
				v_curr = node->get_key();
				smallest_dist = node->get_value();
			}
		}
	}
}

template<class T>
void print_shortest_path(T v, Dictionary<T, T> parent) {
	T* f_result;
	if (parent.Find(v, f_result)) {
		cout << *f_result << " ";
		print_shortest_path(*f_result, parent);
	}
}

template<class T>
void print_distances(T start, Dictionary<T, int> distance, Dictionary<T, T> parent) {
	auto nodes = distance.Nodes();
	auto iterator = nodes.create_list_iterator();
	while (iterator->has_next())
	{
		auto node = iterator->next();
		cout << "Shortest distance from " << start << " to " << node->get_key() << " is: " << node->get_value() << " Expand : " << node->get_key() << " ";
		print_shortest_path(node->get_key(), parent);
		cout << endl;
	}
}

int main() {
	auto g = new Graph<int>();
	Dictionary<int, int> parent;
	Dictionary<int, int> distance;

	g->insert_edge(1, 2, 4);
	g->insert_edge(1, 3, 1);
	g->insert_edge(3, 2, 1);
	g->insert_edge(3, 4, 5);
	g->insert_edge(2, 4, 3);
	g->insert_edge(2, 5, 1);
	g->insert_edge(4, 5, 2);

	int start = 1;
	g->print();
	dijkstra_shortest_path(g, parent, distance, start);
	//print shortest path from vertex 1 to 5
	print_distances(start, distance, parent);

	delete g;
	return 0;
}