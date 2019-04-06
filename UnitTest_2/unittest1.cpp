#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Project_2/RedBlackTree.h"
#include "../Project_2/RedBlackTree.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest_2
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(dictionary_initialize_empty)
		{
			Dictionary<int, int> dictionary;
			Assert::IsTrue(dictionary.get_size() == 0);
		}

		TEST_METHOD(dictionary_insert_all_new)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 0 &&
				keys.at(1) == 0 && values.at(1) == 1 &&
				keys.at(2) == 1 && values.at(2) == 2);
		}

		TEST_METHOD(dictionary_insert_all_exists_same)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);

			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 0 &&
				keys.at(1) == 0 && values.at(1) == 1 &&
				keys.at(2) == 1 && values.at(2) == 2);
		}

		TEST_METHOD(dictionary_count_variable_test)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 0);
			dictionary.Insert(1, 0);
			dictionary.Insert(2, 0);
			dictionary.Insert(3, 0);
			dictionary.Insert(4, 0);

			dictionary.Insert(-1, 0);
			dictionary.Insert(-1, 0);
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 0);
			dictionary.Insert(3, 0);
			dictionary.Insert(3, 0);
			dictionary.Insert(4, 0);
			dictionary.Insert(4, 0);
			dictionary.Insert(4, 0);
			dictionary.Insert(4, 0);
			auto nodes = dictionary.Nodes();
			Assert::IsTrue(dictionary.get_size() == 6 &&
				nodes.at(0)->get_count() == 4 &&
				nodes.at(1)->get_count() == 2 &&
				nodes.at(2)->get_count() == 1 &&
				nodes.at(3)->get_count() == 1 &&
				nodes.at(4)->get_count() == 3 &&
				nodes.at(5)->get_count() == 5);
		}

		TEST_METHOD(dictionary_insert_all_exists_another)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);

			dictionary.Insert(-1, 10);
			dictionary.Insert(0, 21);
			dictionary.Insert(1, 22);
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				keys.at(0) == -1 && values.at(0) == 10 &&
				keys.at(1) == 0 && values.at(1) == 21 &&
				keys.at(2) == 1 && values.at(2) == 22);
		}

		TEST_METHOD(dictionary_keys_non_empty)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				keys.at(0) == -1 &&
				keys.at(1) == 0 &&
				keys.at(2) == 1);
		}

		TEST_METHOD(dictionary_keys_empty)
		{
			Dictionary<int, int> dictionary;
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 0 && keys.isEmpty());
		}

		TEST_METHOD(dictionary_nodes_non_empty)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto nodes = dictionary.Nodes();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				nodes.at(0)->get_key() == -1 && nodes.at(0)->get_value() == 0 &&
				nodes.at(1)->get_key() == 0 && nodes.at(1)->get_value() == 1 &&
				nodes.at(2)->get_key() == 1 && nodes.at(2)->get_value() == 2);
		}

		TEST_METHOD(dictionary_nodes_empty)
		{
			Dictionary<int, int> dictionary;
			auto nodes = dictionary.Nodes();
			Assert::IsTrue(dictionary.get_size() == 0 && nodes.isEmpty());
		}

		TEST_METHOD(dictionary_values_non_empty)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto values = dictionary.Values();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				values.at(0) == 0 &&
				values.at(1) == 1 &&
				values.at(2) == 2);
		}

		TEST_METHOD(dictionary_values_empty)
		{
			Dictionary<int, int> dictionary;
			auto values = dictionary.Values();
			Assert::IsTrue(dictionary.get_size() == 0 && values.isEmpty());
		}

		TEST_METHOD(dictionary_remove_non_empty_exist_first)
		{
			Dictionary<string, int> dictionary;
			dictionary.Insert("first", 0);
			dictionary.Insert("second", 1);
			dictionary.Insert("third", 2);

			dictionary.Remove("first");

			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 2 &&
				keys.at(0) == "second" && values.at(0) == 1 &&
				keys.at(1) == "third" && values.at(1) == 2);
		}

		TEST_METHOD(dictionary_remove_non_empty_exist_second)
		{
			Dictionary<string, int> dictionary;
			dictionary.Insert("first", 0);
			dictionary.Insert("second", 1);
			dictionary.Insert("third", 2);
			dictionary.Remove("second");
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 2 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "third" && values.at(1) == 2);
		}

		TEST_METHOD(dictionary_remove_non_empty_exist_third)
		{
			Dictionary<string, int> dictionary;
			dictionary.Insert("first", 0);
			dictionary.Insert("second", 1);
			dictionary.Insert("third", 2);
			dictionary.Remove("third");
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 2 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "second" && values.at(1) == 1);
		}

		TEST_METHOD(dictionary_remove_empty)
		{
			Dictionary<bool, int> dictionary;
			dictionary.Remove(false);
			Assert::IsTrue(dictionary.get_size() == 0);
		}

		TEST_METHOD(dictionary_remove_non_empty_non_exist_forth)
		{
			Dictionary<string, int> dictionary;
			dictionary.Insert("first", 0);
			dictionary.Insert("second", 1);
			dictionary.Insert("third", 2);
			dictionary.Remove("forth");
			auto values = dictionary.Values();
			auto keys = dictionary.Keys();
			Assert::IsTrue(dictionary.get_size() == 3 &&
				keys.at(0) == "first" && values.at(0) == 0 &&
				keys.at(1) == "second" && values.at(1) == 1 &&
				keys.at(2) == "third" && values.at(2) == 2);
		}

		TEST_METHOD(dictionary_contains_non_empty_non_exist)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto values = dictionary.Values();
			Assert::IsFalse(dictionary.Contains(2));
		}

		TEST_METHOD(dictionary_contains_empty)
		{
			Dictionary<int, int> dictionary;
			auto values = dictionary.Values();
			Assert::IsFalse(dictionary.Contains(0));
		}

		TEST_METHOD(dictionary_contains_non_empty_exist)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			auto values = dictionary.Values();
			Assert::IsTrue(
				dictionary.Contains(-1) &&
				dictionary.Contains(0) &&
				dictionary.Contains(1));
		}

		TEST_METHOD(dictionary_find_non_empty_exist)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			int* value1, * value2, * value3;
			Assert::IsTrue(dictionary.Find(-1, value1) && *value1 == 0 &&
				dictionary.Find(0, value2) && *value2 == 1 &&
				dictionary.Find(1, value3) && *value3 == 2);
		}

		TEST_METHOD(dictionary_find_non_empty_non_exist)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			int* value;
			Assert::IsTrue(!dictionary.Find(2, value));
		}

		TEST_METHOD(dictionary_clear_non_empty)
		{
			Dictionary<int, int> dictionary;
			dictionary.Insert(-1, 0);
			dictionary.Insert(0, 1);
			dictionary.Insert(1, 2);
			dictionary.Clear();
			Assert::IsTrue(dictionary.get_size() == 0);
		}

		TEST_METHOD(dictionary_clear_empty)
		{
			Dictionary<int, int> dictionary;
			dictionary.Clear();
			Assert::IsTrue(dictionary.get_size() == 0);
		}
	};
}