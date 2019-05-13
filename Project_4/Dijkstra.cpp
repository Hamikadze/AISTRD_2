#include "Dijkstra.h"

template <class T>
void Dijkstra<T>::dijkstra_shortest_path(T start)
{
	Dictionary<T, bool> discovered;

	distance.Insert(start, 0);
	T v_curr = start;

	while (!discovered.Find(v_curr)) {
		discovered.Insert(v_curr, true);
		LinkedList<EdgeNode<T>*>** curr_list;
		if (edges.Find(v_curr, curr_list)) {
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

template <class T>
void Dijkstra<T>::get_path(T to, LinkedList<T> & path)
{
	T* f_result;
	if (parent.Find(to, f_result)) {
		path.push_front(*f_result);
		get_path(*f_result, path);
	}
}

template <class T>
LinkedList<T> Dijkstra<T>::get_path(T destination)
{
	LinkedList<T> path;
	this->get_path(destination, path);
	if (!path.isEmpty())
		path.push_back(destination);
	return path;
}

template <class T>
int Dijkstra<T>::shortest_path(T to)
{
	return distance.Find(to);
}

template <class T>
bool Dijkstra<T>::read()
{
	std::ifstream file("Read.txt");
	std::string str;
	while (std::getline(file, str))
	{
		try {
			std::string city_from, city_to, price_to, price_from;
			std::istringstream iss(str);
			iss >> city_from >> city_to >> price_to >> price_from;
			if (city_from.empty() || city_to.empty() || price_to.empty() || price_from.empty())
			{
				throw std::invalid_argument("Input data reading error");
			}
			if (price_to != "N\\A" && is_u_int(price_to))
			{
				this->insert_edge(city_from, city_to, std::stoi(price_to));
			}
			if (price_from != "N\\A" && is_u_int(price_from))
			{
				this->insert_edge(city_to, city_from, std::stoi(price_from));
			}
		}
		catch (std::invalid_argument & e)
		{
			continue;
		}
	}
	return true;
}