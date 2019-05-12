// Project_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "ShennonFano.h"

int main()
{
	system("chcp 1251");//Установка кодовой страницы
	setlocale(LC_ALL, "ru_RU.UTF-8");
	//wcout.imbue(locale("rus_rus.866"));
	std::wstring test_string = L"Ленин — жил. Ленин — жив. Ленин — будет жить.";
	ShennonFano shennon;
	auto table = shennon.get_table(test_string);
	auto encode_str = shennon.encode(test_string, table);
	auto decode_str = shennon.decode(encode_str, table);
	auto table_iterator = table.Nodes().create_list_iterator();
	while (table_iterator->has_next())
	{
		auto table_node = table_iterator->next();

		std::wcout << "Letter : " << table_node->get_key() << " | Code : " << table_node->get_value() << " | Freq: " << table_node->get_count() << std::endl;
	}
	size_t decode_size = (decode_str.size() + 1) * sizeof(wchar_t);
	size_t encode_size = ceil(encode_str.size() / 8.0);
	std::wcout << "Decode string : " << decode_str << " | size : " << decode_size << std::endl;
	std::wcout << "Encode string : " << encode_str << " | size : " << encode_size << std::endl;
	std::cout << "Compression ratio : " << encode_size / (double)decode_size << std::endl;
	return 0;
}