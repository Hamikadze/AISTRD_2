#pragma once
#include "../Project_2/RedBlackTree.h"

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
protected:
	~Graph()
	{
		edges.Clear();
	};
	Dictionary<T, LinkedList<EdgeNode<T>*>*> edges;
	bool edge_exist(T, T);
	int get_edge(T, T);
	void flow_change(T, T, int);
public:
	Graph() = default;
	void insert_edge(T, T, int);
	void print();
};