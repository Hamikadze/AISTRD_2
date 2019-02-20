#pragma once
template <class T>
class LIterator
{
public:
	virtual T next() = 0; // index of data and data
	virtual bool has_next() = 0;
};
