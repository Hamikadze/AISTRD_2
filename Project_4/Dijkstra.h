#pragma once
#include "Graph.cpp"

template<class T>
class Dijkstra : public Graph<T>
{
private:
	using Graph<T>::edges;
	Dictionary<T, T> parent;
	Dictionary<T, int> distance;

	bool is_u_int(const std::string s) const
	{
		return s.find_first_not_of("0123456789") == std::string::npos;
	}
	void shortest_path(T, LinkedList<T>&);

	~Dijkstra() { parent.Clear(); distance.Clear(); edges.Clear(); }
public:
	Dijkstra() : Graph<T>() {};
	void dijkstra_shortest_path(T);
	void print_distances(T);
	LinkedList<T> shortest_path(T);
	bool read();
};
