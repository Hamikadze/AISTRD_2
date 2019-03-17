#include "pch.h"
#include "RedBlackTree.h"

template <class T1, class T2>
void Dictionary<T1, T2>::Insert(T1 key, T2 value) {
	auto* create = new node<T1, T2>(key, value);
	if (root == nullptr)
	{
		root = create;
		create->father = nullptr;
	}
	else
	{
		node<T1, T2>* father = nullptr;
		node<T1, T2>* temp = root;
		while (temp != nullptr)
		{
			father = temp;
			if (temp->key > create->key) temp = temp->left;
			else if (temp->key < create->key) temp = temp->right;
			else {
				temp->value = value;
				return;
			};
		}
		create->father = father;
		if (father->key < create->key) father->right = create;
		else if (father->key > create->key)father->left = create;
		else return;
	}
	insert_fix(create);
}

template<class T1, class T2>
void Dictionary<T1, T2>::insert_fix(node<T1, T2>* input)
{
	node<T1, T2>* temp = input;
	while (temp != root && temp->father->color)
	{
		if (temp->father == temp->father->father->left)
		{
			node<T1, T2>* y = temp->father->father->right;
			if ((y != nullptr) && (y->color))
			{
				temp->father->color = 0;
				y->color = 0;
				temp = temp->father->father;
			}
			else
			{
				if (temp->father->right == temp)
				{
					temp = temp->father;
					rotate_left(temp);
				}
				temp->father->color = 0;
				temp->father->father->color = 1;
				rotate_right(temp->father->father);
			}
		}
		else
		{
			node<T1, T2>* y = temp->father->father->left;
			if ((y != nullptr) && (y->color))
			{
				temp->father->color = 0;
				y->color = 0;
				temp->father->father->color = 1;
				temp = temp->father->father;
			}
			else
			{
				if (temp->father->left == temp)
				{
					temp = temp->father;
					rotate_right(temp);
				}
				temp->father->color = 0;
				temp->father->father->color = 1;
				rotate_left(temp->father->father);
			}
		}
	}
	root->color = false;
}

template<class T1, class T2>
void Dictionary<T1, T2>::rotate_right(node<T1, T2>* input)
{
	if (input->left == nullptr)
		return;
	node<T1, T2> * left = input->left;
	node<T1, T2> * right = left->right;
	node<T1, T2> * father = input->father;
	if (father == nullptr)
	{
		left->father = nullptr;
		root = left;
	}
	else
	{
		left->father = father;
		if (father->left == input)
			father->left = left;
		if (father->right == input)
			father->right = left;
	}
	left->right = input;
	input->father = left;
	input->left = right;
	if (right != nullptr)
		right->father = input;
}

template <class T1, class T2>
void Dictionary<T1, T2>::rotate_left(node<T1, T2> * input)
{
	if (input->right == nullptr)
		return;
	node<T1, T2> * right = input->right;
	node<T1, T2> * left = right->left;
	node<T1, T2> * father = input->father;
	if (father == nullptr)
	{
		right->father = nullptr;
		root = right;
	}
	else
	{
		right->father = father;
		if (father->left == input)
			father->left = right;
		if (father->right == input)
			father->right = right;
	}
	right->left = input;
	input->father = right;
	input->right = left;
	if (left != nullptr)
		left->father = input;
}
template<class T1, class T2>
node<T1, T2> * Dictionary<T1, T2>::node_find(T1 key)
{
	node<T1, T2>* temp = root;
	while (temp != nullptr)
	{
		if (temp->key == key)
			break;
		if (key > temp->key)
			temp = temp->right;
		else if (key < temp->key)
			temp = temp->left;
	}
	if (temp == nullptr)
		return nullptr;
	if (temp->key == key)
		return temp;
	return nullptr;
}

template <class T1, class T2>
void Dictionary<T1, T2>::tree_delete(node<T1, T2> * input)
{
	if (input == nullptr) return;
	tree_delete(input->left);
	tree_delete(input->right);
	delete input;
}

template <class T1, class T2>
node<T1, T2>* Dictionary<T1, T2>::SftIterator::next()
{
	while (current != nullptr) {
		list.push_front(current);
		current = current->left;
	}
	current = list.at(0);
	list.pop_front();
	auto temp = current;
	current = current->right;
	return temp;
}

template <class T1, class T2>
bool Dictionary<T1, T2>::Contains(T1 key)
{
	node<T1, T2>* temp = node_find(key);
	if (temp == nullptr) return false;
	return temp->key == key;
}

template <class T1, class T2>
void Dictionary<T1, T2>::Clear()
{
	tree_delete(root);
	root = nullptr;
}

template <class T1, class T2>
LinkedList<T1> Dictionary<T1, T2>::Keys()
{
	LinkedList<T1> keys;
	if (this->size() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			keys.push_back(iterator->next()->key);
		}
	}
	return keys;
}

template <class T1, class T2>
LinkedList<T2> Dictionary<T1, T2>::Values()
{
	LinkedList<T2> values;
	if (this->size() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			values.push_back(iterator->next()->value);
		}
	}
	return values;
}

template <class T1, class T2>
T2 Dictionary<T1, T2>::Find(T1 key)
{
	node<T1, T2>* temp = node_find(key);
	if (temp == nullptr)
		return {};
	return temp->value;
}

template<class T1, class T2>
size_t Dictionary<T1, T2>::size(node<T1, T2> * input)
{
	if (input == nullptr) return 0;
	return size(input->left) + size(input->right) + 1;
}

template<class T1, class T2>
node<T1, T2>* Dictionary<T1, T2>::successor(node<T1, T2> * input)
{
	node<T1, T2>* temp;
	if (input->left != nullptr)
	{
		temp = input->left;
		while (temp->right != nullptr)
			temp = temp->right;
	}
	else
	{
		temp = input->right;
		while (temp->left != nullptr)
			temp = temp->left;
	}
	return temp;
}

template <class T1, class T2>
void Dictionary<T1, T2>::Remove(T1 key)
{
	if (root == nullptr)
	{
		return;
	}
	node<T1, T2>* replaceable = root;
	bool found = false;
	while (replaceable != nullptr && !found)
	{
		if (replaceable->key == key)
			found = true;
		if (!found)
		{
			if (replaceable->key < key)
				replaceable = replaceable->right;
			else
				replaceable = replaceable->left;
		}
	}
	if (!found)
		return;
	node<T1, T2>* removable;
	node<T1, T2>* temp;
	if (replaceable->left == nullptr || replaceable->right == nullptr)
		removable = replaceable;
	else
		removable = successor(replaceable);
	if (removable->left != nullptr)
		temp = removable->left;
	else
	{
		if (removable->right != nullptr)
			temp = removable->right;
		else
			temp = nullptr;
	}
	if (temp != nullptr)
		temp->father = removable->father;
	if (removable->father == nullptr)
		root = temp;
	else
	{
		if (removable == removable->father->left)
			removable->father->left = temp;
		else
			removable->father->right = temp;
	}
	if (removable != replaceable)
	{
		replaceable->color = removable->color;
		replaceable->key = removable->key;
		replaceable->value = removable->value;
	}
	if (removable->color == 0)
		delete_fix(temp);
}

template <class T1, class T2>
void Dictionary<T1, T2>::delete_fix(node<T1, T2> * input)
{
	if (input != nullptr)
	{
		node<T1, T2>* temp;
		while (input != root && !input->color)
		{
			if (input->father->left == input)
			{
				temp = input->father->right;
				if (temp->color == 1)
				{
					temp->color = 0;
					input->father->color = 1;
					rotate_left(input->father);
					temp = input->father->right;
				}
				if (!temp->right->color && !temp->left->color)
				{
					temp->color = 1;
					input = input->father;
				}
				else
				{
					if (!temp->right->color)
					{
						temp->left->color = 0;
						temp->color = 1;
						rotate_right(temp);
						temp = input->father->right;
					}
					temp->color = input->father->color;
					input->father->color = 0;
					temp->right->color = 0;
					rotate_left(input->father);
					input = root;
				}
			}
			else
			{
				temp = input->father->left;
				if (temp->color)
				{
					temp->color = 1;
					input->father->color = 1;
					rotate_right(input->father);
					temp = input->father->left;
				}
				if (!temp->left->color && !temp->right->color)
				{
					temp->color = 1;
					input = input->father;
				}
				else
				{
					if (!temp->left->color)
					{
						temp->right->color = 0;
						temp->color = 1;
						rotate_left(temp);
						temp = input->father->left;
					}
					temp->color = input->father->color;
					input->father->color = 0;
					temp->left->color = 0;
					rotate_right(input->father);
					input = root;
				}
			}
			input->color = 0;
			root->color = 0;
		}
	}
}