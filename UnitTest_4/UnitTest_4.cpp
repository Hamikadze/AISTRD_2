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

		TEST_METHOD(min_lenght_path_test_string)
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

		TEST_METHOD(min_lenght_path_test_int_single)
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

		TEST_METHOD(min_lenght_path_test_int_multiply)
		{
			auto g = new Dijkstra<int>();
			g->insert_edge(1, 2, 1);
			g->insert_edge(1, 5, 2);
			g->insert_edge(1, 3, 4);
			g->insert_edge(3, 1, 4);
			g->insert_edge(2, 4, 9);
			g->insert_edge(4, 2, 9);
			g->insert_edge(3, 4, 7);
			g->insert_edge(4, 3, 7);
			g->insert_edge(5, 6, 8);
			g->insert_edge(4, 6, 2);

			auto start = 1;
			g->dijkstra_shortest_path(start);

			Assert::IsTrue(g->shortest_path(1) == 0 &&
				g->shortest_path(2) == 1 &&
				g->shortest_path(3) == 4 &&
				g->shortest_path(4) == 10 &&
				g->shortest_path(5) == 2 &&
				g->shortest_path(6) == 10);
		}

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
			auto shortest_path = g->get_path("Vdk");
			auto iterator = shortest_path.create_list_iterator();
			Assert::IsTrue(iterator->next() == "Msk" && iterator->next() == "Spb" && iterator->next() == "Vdk");
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
			auto shortest_path = g->get_path(5);
			auto iterator = shortest_path.create_list_iterator();
			Assert::IsTrue(iterator->next() == 1 && iterator->next() == 3 && iterator->next() == 2);
		}

		TEST_METHOD(min_path_test_int_2)
		{
			auto g = new Dijkstra<int>();
			g->insert_edge(1, 2, 1);
			g->insert_edge(1, 5, 2);
			g->insert_edge(1, 3, 4);
			g->insert_edge(3, 1, 4);
			g->insert_edge(2, 4, 9);
			g->insert_edge(4, 2, 9);
			g->insert_edge(3, 4, 7);
			g->insert_edge(4, 3, 7);
			g->insert_edge(5, 6, 8);
			g->insert_edge(4, 6, 2);

			auto start = 1;
			g->dijkstra_shortest_path(start);
			auto shortest_path = g->get_path(6);
			auto iterator = shortest_path.create_list_iterator();
			Assert::IsTrue(iterator->next() == 1 && iterator->next() == 5 && iterator->next() == 6);
		}
	};
}