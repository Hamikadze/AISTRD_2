#pragma once

#include "../Project_4/Graph.cpp"

template<class T>
class FordFulkerson : public Graph<T>
{
private:
	using Graph<T>::edges;
	~FordFulkerson();
	bool bfs(int from, int to, Dictionary<int, int>& parent);

	bool is_u_int(const std::string s) const
	{
		return s.find_first_not_of("0123456789") == std::string::npos;
	}
	int min(int val1, int val2) { return val1 <= val2 ? val1 : val2; }
public:
	FordFulkerson() : Graph<T>() {};
	bool read();
	int fordFulkerson(int from, int to);
};
