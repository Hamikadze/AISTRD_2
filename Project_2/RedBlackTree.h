#pragma once
#include <iostream>
#include "../Project_1/LinkedList.h"
#include "../Project_1/LinkedList.cpp"
using namespace std;

enum Color { RED, BLACK }; // RED - false, BLACK - true
template <class T1, class T2> class Dictionary;

template<class T1, class T2> //T1 - key type, T2 - value type
struct Node
{
private:
	friend Dictionary<T1, T2>;
	T1 key;
	T2 value;
	unsigned int count;//number of inserts with value changes
	bool color;
	Node* left, * right, * parent;
	Node(T1 key, T2 value)
	{
		this->key = key;
		this->value = value;
		this->count = 1;
		color = RED;
		left = right = parent = nullptr;
	}
public:
	T1 get_key() { return this->key; }
	T2 get_value() { return this->value; }
	unsigned int get_count() { return this->count; }
};

template<class T1, class T2> //T1 - key type, T2 - value type
class Dictionary
{
private:
	Node<T1, T2>* root;
	int size;
protected:
	void rotateLeft(Node<T1, T2>*&);
	void rotateRight(Node<T1, T2>*&);
	void fixInsertRBTree(Node<T1, T2>*&);
	void fixDeleteRBTree(Node<T1, T2>*&);
	static bool getColor(Node<T1, T2>*&);
	static void setColor(Node<T1, T2>*&, bool);
	static Node<T1, T2>* minValueNode(Node<T1, T2>*);
	static Node<T1, T2>* maxValueNode(Node<T1, T2>*);
	Node<T1, T2>* insertBST(Node<T1, T2>*, Node<T1, T2>*);
	Node<T1, T2>* deleteBST(Node<T1, T2>*, T1);
	int getBlackHeight(Node<T1, T2>*);
	void tree_delete(Node<T1, T2>*);
	Node<T1, T2>* node_find(Node<T1, T2>*, T1);

	class SftIterator : public Iterator<Node<T1, T2>*>
	{
	public:
		SftIterator(Node < T1, T2>* root)
		{
			current = root;
		};

	private:
		Node<T1, T2>* next() override;
		bool has_next() override
		{
			return (list.get_size() || current != nullptr);
		};
		LinkedList<Node<T1, T2>*> list;
		Node<T1, T2>* current;
	};
	Iterator<Node<T1, T2>*>* create_sft_iterator() const
	{
		if (this == nullptr && this->root == nullptr) throw std::exception("Dictionary does not exist");
		return new SftIterator(this->root);
	};
public:
	Dictionary() { root = nullptr; size = 0; };
	~Dictionary() { Clear(); }
	size_t get_size()
	{
		return size;
	};
	void Insert(T1 key, T2 value); //insert key and value to dictionary, or replace value by key
	void Remove(T1);
	T2* Find(T1); //return nullptr if not find
	bool Contains(T1 key);
	void Clear(); //clear whole dictionary
	LinkedList<Node<T1, T2>*> Nodes();
	LinkedList<T1> Keys();
	LinkedList<T2> Values();
};
