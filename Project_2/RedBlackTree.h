#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include "../Project_1/LinkedList.h"
#include "../Project_1/LinkedList.cpp"
using namespace std;

template <class T1, class T2> class Dictionary;

template <class T1, class T2> class node
{
private:
	T1 key;
	T2 value;
	node *father;
	node *left;
	node *right;
	bool color; //red = true, black = false
	node(T1 key, T2 value)
	{
		this->key = key;
		this->value = value;
		left = nullptr;
		right = nullptr;
		father = nullptr;
		color = true;
	}
	friend Dictionary<T1, T2>;
};

template <class T1, class T2> class Dictionary
{
	node<T1, T2> *root;
	size_t size(node<T1, T2>*); //return size of tree
	void rotate_left(node<T1, T2>*); //rotate to left
	void rotate_right(node<T1, T2>*); //rotate to right
	void insert_fix(node<T1, T2>*); //call after insert, fix tree height
	node<T1, T2>* successor(node<T1, T2>*); //find successor for node, call in delete
	void delete_fix(node<T1, T2>*); //call after delete, fix tree height
	node<T1, T2>* node_find(T1 key); //find and return node, return nullprt if not find
	void tree_delete(node<T1, T2>*); //delete node
	class SftIterator : public Iterator<node<T1, T2> *>
	{
	public:
		SftIterator(node < T1, T2> * root)
		{
			current = root;
		};

	private:
		node<T1, T2>* next() override;
		bool has_next() override
		{
			return (list.get_size() || current != nullptr);
		};
		LinkedList<node<T1, T2>*> list;
		node<T1, T2> * current;
	};
	Iterator<node<T1, T2> *>* create_sft_iterator() const
	{
		if (this == nullptr && this->root == nullptr) throw std::exception("Dictionary does not exist");
		return new SftIterator(this->root);
	};
public:
	size_t size()
	{
		return size(root);
	};

	Dictionary() { root = nullptr; };
	~Dictionary() { Clear(); }
	void Insert(T1 key, T2 value); //insert key and value to dictionary, or replace value by key
	void Remove(T1);
	T2 Find(T1); //return nullptr if not find
	bool Contains(T1 key);
	void Clear(); //clear whole dictionary
	LinkedList<T1> Keys();
	LinkedList<T2> Values();
};
