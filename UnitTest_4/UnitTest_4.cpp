#include "pch.h"
#include "CppUnitTest.h"
#include "../Project_4/Dijkstra.cpp"
#include "../Project_4/Dijkstra.h"
#include "../Project_3/ShennonFano.h"
#include "../Project_3/ShennonFano.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest4
{
	TEST_CLASS(UnitTest4)
	{
	public:

		TEST_METHOD(min_path_test_string)
		{
			auto g = new Dijkstra<std::string>();
			g->insert_edge("Msk", "Vdk", 4);
			g->insert_edge("Msk", "Spb", 1);
			g->insert_edge("Spb", "Vdk", 1);
			g->insert_edge("Spb", "Omsk", 5);
			g->insert_edge("Vdk", "Omsk", 3);
			g->insert_edge("Vdk", "Tula", 1);
			g->insert_edge("Omsk", "Tula", 2);

			string start = "Msk";
			g->dijkstra_shortest_path(start);
			auto shortest_path = g->shortest_path("Vdk");

			Assert::AreEqual(shortest_path, 2);
		}

		TEST_METHOD(min_path_test_int_1)
		{
			auto g = new Dijkstra<int>();
			g->insert_edge(1, 2, 4);
			g->insert_edge(1, 3, 1);
			g->insert_edge(3, 2, 1);
			g->insert_edge(3, 4, 5);
			g->insert_edge(2, 4, 3);
			g->insert_edge(2, 5, 1);
			g->insert_edge(4, 5, 2);

			auto start = 1;
			g->dijkstra_shortest_path(start);
			auto shortest_path = g->shortest_path(5);

			Assert::AreEqual(shortest_path, 3);
		}

		TEST_METHOD(min_path_test_int_2)
		{
			auto g = new Dijkstra<int>();
			g->insert_edge(1, 2, 10);
			g->insert_edge(1, 3, 30);
			g->insert_edge(1, 4, 50);
			g->insert_edge(1, 5, 10);
			g->insert_edge(4, 2, 40);
			g->insert_edge(4, 3, 20);
			g->insert_edge(5, 1, 10);
			g->insert_edge(5, 4, 30);

			auto start = 1;
			g->dijkstra_shortest_path(start);
			auto shortest_path = g->shortest_path(3);

			Assert::AreEqual(shortest_path, 20);
		}
	};
}