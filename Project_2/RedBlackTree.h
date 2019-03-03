#pragma once
#include <stack>
#include <queue>
#include <iostream>
#include "../Project_1/LinkedList.h"
#include "../Project_1/LinkedList.cpp"
using namespace std;

template <class T1, class T2> class node
{
public:
	T1 key;
	T2 value;
	node *father;
	node *left;
	node *right;
	bool color;

	node(T1 key, T2 value)
	{
		this->key = key;
		this->value = value;
		left = nullptr;
		right = nullptr;
		father = nullptr;
		color = true;
	}
};

template <class T1, class T2> class Tree
{
	node<T1, T2> *root;
	size_t size(node<T1, T2>*);
	void rotate_left(node<T1, T2>*);
	void rotate_right(node<T1, T2>*);
	void insert_fix(node<T1, T2>*);
	Tree(node<T1, T2>*);
	node<T1, T2>* successor(node<T1, T2>*);
	void delete_fix(node<T1, T2>*);
	size_t size();
	int black_hight() const;
	node<T1, T2>* node_find(T1 key);
	void tree_delete(node<T1, T2>*);
	class SftIterator : public Iterator<node<T1, T2> *>
	{
	public:
		SftIterator(node < T1, T2> * root)
		{
			current = root;
		};

	private:
		node<T1, T2>* next() override;
		bool has_next() override;
		LinkedList<node<T1, T2>*> list;
		node<T1, T2> * current;
	};
public:
	Iterator<node<T1, T2> *>* create_sft_iterator() const;
	Tree() :root(nullptr) {};
	~Tree() { Clear(); }
	void Insert(T1 key, T2 value);
	void Remove(T1);
	T2 Find(T1);
	bool Contains(T1 key);
	void Clear();
	LinkedList<T1> Keys();
	LinkedList<T2> Values();
};

template <class T1, class T2>
Iterator<node<T1, T2> *>* Tree<T1, T2>::create_sft_iterator() const
{
	if (this == nullptr && this->root == nullptr) throw std::exception("Tree does not exist");
	return new SftIterator(this->root);
}

template <class T1, class T2>
Tree<T1, T2>::Tree(node<T1, T2> * key)
{
	root = key;
}

template <class T1, class T2>
void Tree<T1, T2>::Insert(T1 key, T2 value) {
	node<T1, T2> *create = new node<T1, T2>(key, value);
	node<T1, T2> *p = root;
	node<T1, T2> *q = nullptr;
	if (root == nullptr)
	{
		root = create;
		create->father = nullptr;
	}
	else
	{
		while (p != nullptr)
		{
			q = p;
			if (p->key > create->key) p = p->left;
			else if (p->key < create->key) p = p->right;
			else {
				p->value = value;
				return;
			};
		}
		create->father = q;
		if (q->key < create->key) q->right = create;
		else if (q->key > create->key)q->left = create;
		else return;
	}
	insert_fix(create);
}

template<class T1, class T2>
void Tree<T1, T2>::insert_fix(node<T1, T2> *p)
{
	node<T1, T2> *x = p;
	while (x != root && x->father->color)
	{
		if (x->father == x->father->father->left)
		{
			node<T1, T2> *y = x->father->father->right;
			if ((y != nullptr) && (y->color))
			{
				x->father->color = 0;
				y->color = 0;
				x->father->father->color;
				x = x->father->father;
			}
			else
			{
				if (x->father->right == x)
				{
					x = x->father;
					rotate_left(x);
				}
				x->father->color = 0;
				x->father->father->color = 1;
				rotate_right(x->father->father);
			}
		}
		else
		{
			node<T1, T2> *y = x->father->father->left;
			if ((y != nullptr) && (y->color))
			{
				x->father->color = 0;
				y->color = 0;
				x->father->father->color = 1;
				x = x->father->father;
			}
			else
			{
				if (x->father->left == x)
				{
					x = x->father;
					rotate_right(x);
				}
				x->father->color = 0;
				x->father->father->color = 1;
				rotate_left(x->father->father);
			}
		}
	}
	root->color = 0;
}

template<class T1, class T2>
void Tree<T1, T2>::rotate_right(node<T1, T2>* y)
{
	if (y->left == nullptr)
		return;
	node<T1, T2> *x = y->left;
	node<T1, T2> *b = x->right;
	node<T1, T2> *f = y->father;
	if (f == nullptr)
	{
		x->father = nullptr;
		root = x;
	}
	else
	{
		x->father = f;
		if (f->left == y)
			f->left = x;
		if (f->right == y)
			f->right = x;
	}
	x->right = y;
	y->father = x;
	y->left = b;
	if (b != nullptr)
		b->father = y;
}

template <class T1, class T2>
void Tree<T1, T2>::rotate_left(node<T1, T2>* x)
{
	if (x->right == nullptr)
		return;
	node<T1, T2> *y = x->right;
	node<T1, T2> *b = y->left;
	node<T1, T2> *f = x->father;
	if (f == nullptr)
	{
		y->father = nullptr;
		root = y;
	}
	else
	{
		y->father = f;
		if (f->left == x)
			f->left = y;
		if (f->right == x)
			f->right = y;
	}
	y->left = x;
	x->father = y;
	x->right = b;
	if (b != nullptr)
		b->father = x;
}
template<class T1, class T2>
node<T1, T2>* Tree<T1, T2>::node_find(T1 key)
{
	node<T1, T2> *t = root;
	while (t != nullptr)
	{
		if (t->key == key)
			break;
		if (key > t->key)
			t = t->right;
		else if (key < t->key)
			t = t->left;
	}
	if (t == nullptr)
		return nullptr;
	if (t->key == key)
		return t;
	return nullptr;
}

template <class T1, class T2>
void Tree<T1, T2>::tree_delete(node<T1, T2> * p)
{
	if (p == nullptr) return;
	tree_delete(p->left);
	tree_delete(p->right);
	free(p);
}

template <class T1, class T2>
node<T1, T2>* Tree<T1, T2>::SftIterator::next()
{
	while (current != nullptr) {
		list.push_front(current);
		current = current->left;
	}
	current = list.at(0);
	list.pop_front();
	auto p = current;
	current = current->right;
	return p;
}

template <class T1, class T2>
bool Tree<T1, T2>::SftIterator::has_next()
{
	return (list.get_size() || current != nullptr);
}

template <class T1, class T2>
bool Tree<T1, T2>::Contains(T1 key)
{
	node<T1, T2> *t = node_find(key);
	if (t == nullptr) return false;
	return t->key == key;
}

template <class T1, class T2>
void Tree<T1, T2>::Clear()
{
	tree_delete(root);
}

template <class T1, class T2>
LinkedList<T1> Tree<T1, T2>::Keys()
{
	LinkedList<T1> keys;
	auto* iterator = this->create_sft_iterator();
	while (iterator->has_next())
	{
		keys.push_back(iterator->next()->key);
	}
	return keys;
}

template <class T1, class T2>
LinkedList<T2> Tree<T1, T2>::Values()
{
	LinkedList<T1> values;
	auto* iterator = this->create_sft_iterator();
	while (iterator->has_next())
	{
		values.push_back(iterator->next()->value);
	}
	return values;
}

template <class T1, class T2>
T2 Tree<T1, T2>::Find(T1 key)
{
	node<T1, T2> *t = node_find(key);
	if (t == nullptr)
		return {};
	return t->value;
}

template<class T1, class T2>
int Tree<T1, T2>::black_hight() const
{
	node<T1, T2> *p = root;
	int num = 0;
	while (p != nullptr) {
		if (p->color == 0) num++;
		p = p->left;
	}
	return num;
}

template<class T1, class T2>
size_t Tree<T1, T2>::size()
{
	return size(root);
}

template<class T1, class T2>
size_t Tree<T1, T2>::size(node<T1, T2> * p)
{
	if (p == nullptr) return 0;
	return size(p->left) + size(p->right) + 1;
}

template<class T1, class T2>
node<T1, T2>* Tree<T1, T2>::successor(node<T1, T2> *p)
{
	node<T1, T2> *y;
	if (p->left != nullptr)
	{
		y = p->left;
		while (y->right != nullptr)
			y = y->right;
	}
	else
	{
		y = p->right;
		while (y->left != nullptr)
			y = y->left;
	}
	return y;
}

template <class T1, class T2>
void Tree<T1, T2>::Remove(T1 key)
{
	if (root == nullptr)
	{
		return;
	}
	node<T1, T2> *p = root;
	node<T1, T2> *y;
	node<T1, T2> *q;
	int found = 0;
	while (p != nullptr && found == 0)
	{
		if (p->key == key)
			found = 1;
		if (found == 0)
		{
			if (p->key < key)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == 0)
		return;
	if (p->left == nullptr || p->right == nullptr)
		y = p;
	else
		y = successor(p);
	if (y->left != nullptr)
		q = y->left;
	else
	{
		if (y->right != nullptr)
			q = y->right;
		else
			q = nullptr;
	}
	if (q != nullptr)
		q->father = y->father;
	if (y->father == nullptr)
		root = q;
	else
	{
		if (y == y->father->left)
			y->father->left = q;
		else
			y->father->right = q;
	}
	if (y != p)
	{
		p->color = y->color;
		p->key = y->key;
	}
	if (y->color == 0)
		delete_fix(q);
}

template <class T1, class T2>
void Tree<T1, T2>::delete_fix(node<T1, T2> *p)
{
	if (p != nullptr)
	{
		node<T1, T2> *s;
		while (p != root && !p->color)
		{
			if (p->father->left == p)
			{
				s = p->father->right;
				if (s->color == 1)
				{
					s->color = 0;
					p->father->color = 1;
					rotate_left(p->father);
					s = p->father->right;
				}
				if (!s->right->color && !s->left->color)
				{
					s->color = 1;
					p = p->father;
				}
				else
				{
					if (!s->right->color)
					{
						s->left->color = 0;
						s->color = 1;
						rotate_right(s);
						s = p->father->right;
					}
					s->color = p->father->color;
					p->father->color = 0;
					s->right->color = 0;
					rotate_left(p->father);
					p = root;
				}
			}
			else
			{
				s = p->father->left;
				if (s->color)
				{
					s->color = 1;
					p->father->color = 1;
					rotate_right(p->father);
					s = p->father->left;
				}
				if (!s->left->color && !s->right->color)
				{
					s->color = 1;
					p = p->father;
				}
				else
				{
					if (!s->left->color)
					{
						s->right->color = 0;
						s->color = 1;
						rotate_left(s);
						s = p->father->left;
					}
					s->color = p->father->color;
					p->father->color = 0;
					s->left->color = 0;
					rotate_right(p->father);
					p = root;
				}
			}
			p->color = 0;
			root->color = 0;
		}
	}
}
