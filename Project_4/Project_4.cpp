#include <iostream>
#include <limits>
#include "../Project_2/RedBlackTree.cpp"
#include "Dijkstra.cpp"
using namespace std;

int main() {
	auto g = new Dijkstra<string>();
	if (g->read()) {
		//g->insert_edge("Msk", "Vdk", 4);
		//g->insert_edge("Msk", "Spb", 1);
		//g->insert_edge("Spb", "Vdk", 1);
		//g->insert_edge("Spb", "Omsk", 5);
		//g->insert_edge("Vdk", "Omsk", 3);
		//g->insert_edge("Vdk", "Tula", 1);
		//g->insert_edge("Omsk", "Tula", 2);

		string start = "1";
		g->print();
		g->dijkstra_shortest_path(start);
		//print shortest path from vertex 1 to 5
		g->print_distances(start);
		auto short_path = g->shortest_path("3");
		auto short_path_iterator = short_path.create_list_iterator();
		while (short_path_iterator->has_next())
		{
			cout << short_path_iterator->next() << " ";
		}
	}
	return 0;
}