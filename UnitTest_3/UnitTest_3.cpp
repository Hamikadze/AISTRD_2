#include "pch.h"
#include "CppUnitTest.h"
#include "../Project_3/ShennonFano.h"
#include "../Project_3/ShennonFano.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest3
{
	TEST_CLASS(UnitTest3)
	{
	public:

		TEST_METHOD(Table_gen_same_frequency)
		{
			std::wstring test_string = L"abc";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			LinkedList<Node<wchar_t, std::wstring>*> nodes = table.Nodes();
			Assert::IsTrue(nodes.at(0)->get_count() == 1 && nodes.at(1)->get_count() == 1 && nodes.at(2)->get_count() == 1);
		}

		TEST_METHOD(Table_gen_diff_frequency)
		{
			std::wstring test_string = L"aaababarrcd"; //a 5 b 2 r 2 c 1 d 1
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			LinkedList<Node<wchar_t, std::wstring>*> nodes = table.Nodes();
			Assert::IsTrue(nodes.at(0)->get_count() == 5 && nodes.at(1)->get_count() == 2 && nodes.at(2)->get_count() == 1 && nodes.at(3)->get_count() == 1 && nodes.at(4)->get_count() == 2);
		}

		TEST_METHOD(Table_gen_same_codes)
		{
			std::wstring test_string = L"abc"; //a 2/0 b 2/10 c 1/11
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			std::wstring* value_a, * value_b, * value_r, * value_c, * value_d;
			table.Find(L'a', value_a);
			table.Find(L'b', value_b);
			table.Find(L'c', value_c);
			Assert::IsTrue(*value_a == L"10" && *value_b == L"11" && *value_c == L"0");
		}

		TEST_METHOD(Table_gen_diff_codes)
		{
			std::wstring test_string = L"aaababarrcd"; //a 5/0 b 2/110 r 2/10 c 1/1110 d 1/1111
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			std::wstring* value_a, * value_b, * value_r, * value_c, * value_d;
			table.Find(L'a', value_a);
			table.Find(L'b', value_b);
			table.Find(L'r', value_r);
			table.Find(L'c', value_c);
			table.Find(L'd', value_d);
			Assert::IsTrue(*value_a == L"0" && *value_b == L"110" && *value_r == L"10" && *value_c == L"1110" && *value_d == L"1111");
		}

		TEST_METHOD(Table_gen_empty)
		{
			std::wstring test_string = L"";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			Assert::IsTrue(table.get_size() == 0);
		}

		TEST_METHOD(ShennonFano_encode_empty_input_string)
		{
			std::wstring test_string = L"";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto encode_str = shennon.encode(test_string, table);
			Assert::IsTrue(encode_str.compare(L"") == 0);
		}

		TEST_METHOD(ShennonFano_encode_empty_table)
		{
			std::wstring test_string = L"гигабайт";
			ShennonFano shennon;
			auto table = shennon.get_table(L"");
			auto encode_str = shennon.encode(test_string, table);
			Assert::IsTrue(encode_str.compare(L"") == 0);
		}
		TEST_METHOD(ShennonFano_encode_incorrect_input_string)
		{
			std::wstring test_string = L"гигабайт";
			std::wstring test_string2 = L"~гигатайд";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto encode_str = shennon.encode(test_string2, table);
			Assert::IsTrue(encode_str.compare(L"00110000110001111") == 0);
		}

		TEST_METHOD(ShennonFano_encode_correct_input_string)
		{
			std::wstring test_string = L"гигабайт";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto encode_str = shennon.encode(test_string, table);
			Assert::IsTrue(encode_str.compare(L"00110000110101111100") == 0);
		}

		TEST_METHOD(ShennonFano_decode_empty_input_string)
		{
			std::wstring test_string = L"";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto decode_str = shennon.decode(test_string, table);
			Assert::IsTrue(decode_str.compare(L"") == 0);
		}

		TEST_METHOD(ShennonFano_decode_empty_table)
		{
			std::wstring test_string = L"00110000110001111";
			ShennonFano shennon;
			auto table = shennon.get_table(L"");
			auto decode_str = shennon.decode(test_string, table);
			Assert::IsTrue(decode_str.compare(L"") == 0);
		}
		TEST_METHOD(ShennonFano_decode_incorrect_input_string)
		{
			std::wstring test_string = L"гигабайт";
			std::wstring test_string2 = L"001100001любаястроканекод";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto decode_str = shennon.decode(test_string2, table);
			Assert::IsTrue(decode_str.compare(L"гига") == 0);
		}

		TEST_METHOD(ShennonFano_decode_correct_input_string)
		{
			std::wstring test_string = L"гигабайт";
			std::wstring test_encode_string = L"00110000110101111100";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto decode_str = shennon.decode(test_encode_string, table);
			Assert::IsTrue(decode_str.compare(L"гигабайт") == 0);
		}

		/*TEST_METHOD(Table_gen_diff_frequency)
		{
			std::wstring test_string = L"гигабайт";
			std::wstring test_string2 = L"~гигатайд";
			ShennonFano shennon;
			auto table = shennon.get_table(test_string);
			auto encode_str = shennon.encode(test_string2, table);
			auto decode_str = shennon.decode(encode_str, table);
		}*/
	};
}