#include "pch.h"
#include "RedBlackTree.h"
using namespace std;

template <class T1, class T2>
void Dictionary<T1, T2>::rotateLeft(Node<T1, T2>*& node)
{
	Node<T1, T2>* right_child = node->right;
	node->right = right_child->left;

	if (node->right != nullptr)
		node->right->parent = node;

	right_child->parent = node->parent;

	if (node->parent == nullptr)
		root = right_child;
	else if (node == node->parent->left)
		node->parent->left = right_child;
	else
		node->parent->right = right_child;

	right_child->left = node;
	node->parent = right_child;
}

template <class T1, class T2>
void Dictionary<T1, T2>::rotateRight(Node<T1, T2> * &node)
{
	Node<T1, T2>* left_child = node->left;
	node->left = left_child->right;

	if (node->left != nullptr)
		node->left->parent = node;

	left_child->parent = node->parent;

	if (node->parent == nullptr)
		root = left_child;
	else if (node == node->parent->left)
		node->parent->left = left_child;
	else
		node->parent->right = left_child;

	left_child->right = node;
	node->parent = left_child;
}

template <class T1, class T2>
void Dictionary<T1, T2>::fixInsertRBTree(Node<T1, T2> * &node)
{
	Node<T1, T2>* parent = nullptr;
	Node<T1, T2>* grandparent = nullptr;
	while (node != root && getColor(node) == RED && getColor(node->parent) == RED) {
		parent = node->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			Node<T1, T2>* uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				node = grandparent;
			}
			else {
				if (node == parent->right) {
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);
				swap(parent->color, grandparent->color);
				node = parent;
			}
		}
		else {
			Node<T1, T2>* uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				node = grandparent;
			}
			else {
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				swap(parent->color, grandparent->color);
				node = parent;
			}
		}
	}
	setColor(root, BLACK);
}

template <class T1, class T2>
void Dictionary<T1, T2>::fixDeleteRBTree(Node<T1, T2> * &node)
{
	if (node == nullptr)
		return;

	if (node == root) {
		root = nullptr;
		size--;
		return;
	}

	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		Node<T1, T2>* child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) {
			node->parent->left = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
			size--;
		}
		else {
			node->parent->right = child;
			if (child != nullptr)
				child->parent = node->parent;
			setColor(child, BLACK);
			delete (node);
			size--;
		}
	}
	else {
		Node<T1, T2>* sibling = nullptr;
		Node<T1, T2>* parent = nullptr;
		Node<T1, T2>* temp = node;
		//setColor(node, DOUBLE_BLACK);
		while (temp != root && /*getColor(node) == DOUBLE_BLACK*/ temp->right == nullptr && temp->left == nullptr) { // check if not root and while leaf (both == nullprt)
			parent = temp->parent;
			if (temp == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						temp = parent;
					}
					else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED)
							setColor(parent, BLACK);
						temp = parent;
					}
					else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left)
			node->parent->left = nullptr;
		else
			node->parent->right = nullptr;
		delete(node);
		size--;
		setColor(root, BLACK);
	}
}

template <class T1, class T2>
bool Dictionary<T1, T2>::getColor(Node<T1, T2> * &node)
{
	if (node == nullptr)
		return BLACK;

	return node->color;
}

template <class T1, class T2>
void Dictionary<T1, T2>::setColor(Node<T1, T2> * &node, bool color)
{
	if (node == nullptr)
		return;

	node->color = color;
}

template <class T1, class T2>
Node<T1, T2>* Dictionary<T1, T2>::minValueNode(Node<T1, T2> * node) {
	while (node->left != nullptr)
		node = node->left;
	return node;
}

template <class T1, class T2>
Node<T1, T2>* Dictionary<T1, T2>::maxValueNode(Node<T1, T2> * node)
{
	while (node->right != nullptr)
		node = node->right;
	return node;
}

template <class T1, class T2>
Node<T1, T2>* Dictionary<T1, T2>::insertBST(Node<T1, T2> * root, Node<T1, T2> * node)
{
	if (root == nullptr) {
		size++;
		return node;
	}

	if (root->key > node->key) {
		root->left = insertBST(root->left, node);
		root->left->parent = root;
	}
	else if (root->key < node->key) {
		root->right = insertBST(root->right, node);
		root->right->parent = root;
	}
	else if (root->key == node->key) {
		root->value = node->value;
		++root->count;
	}

	return root;
}

template <class T1, class T2>
Node<T1, T2>* Dictionary<T1, T2>::deleteBST(Node<T1, T2> * root, T1 key)
{
	if (root == nullptr) {
		return root;
	}

	if (key < root->key)
		return deleteBST(root->left, key);

	if (key > root->key)
		return deleteBST(root->right, key);

	if (root->left == nullptr || root->right == nullptr)
		return root;

	Node<T1, T2> * temp = minValueNode(root->right);
	root->key = temp->key;
	root->value = temp->value;
	return deleteBST(root->right, temp->key);
}

template <class T1, class T2>
int Dictionary<T1, T2>::getBlackHeight(Node<T1, T2> * node)
{
	int count = 0;
	while (node != nullptr) {
		if (getColor(node) == BLACK)
			count++;
		node = node->left;
	}
	return count;
}

template <class T1, class T2>
void Dictionary<T1, T2>::tree_delete(Node<T1, T2> * node)
{
	if (node == nullptr) return;
	tree_delete(node->left);
	tree_delete(node->right);
	node = nullptr;
	delete node;
	size--;
}

template <class T1, class T2>
Node<T1, T2>* Dictionary<T1, T2>::node_find(Node<T1, T2> * node, T1 key)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
		return node_find(node->left, key);
	if (key > node->key)
		return node_find(node->right, key);
	if (node->key == key)
		return node;
	return nullptr;
}

template <class T1, class T2>
Node<T1, T2> * Dictionary<T1, T2>::SftIterator::next()
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
void Dictionary<T1, T2>::Insert(T1 key, T2 value)
{
	auto* node = new Node<T1, T2>(key, value);
	root = insertBST(root, node);
	fixInsertRBTree(node);
}

template <class T1, class T2>
void Dictionary<T1, T2>::Remove(T1 key)
{
	Node<T1, T2>* node = deleteBST(root, key);
	fixDeleteRBTree(node);
}

template <class T1, class T2>
bool Dictionary<T1, T2>::Find(T1 key, T2 * &value)
{
	Node<T1, T2>* temp = node_find(root, key);
	if (temp == nullptr)
		return false;
	value = &temp->value;
	return true;
}

template <class T1, class T2>
bool Dictionary<T1, T2>::Contains(T1 key)
{
	Node<T1, T2>* temp = node_find(root, key);
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
LinkedList<Node<T1, T2>*> Dictionary<T1, T2>::Nodes()
{
	LinkedList<Node<T1, T2>*> nodes;
	if (this->get_size() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			nodes.push_back(iterator->next());
		}
	}
	return nodes;
}

template <class T1, class T2>
LinkedList<T1> Dictionary<T1, T2>::Keys()
{
	LinkedList<T1> keys;
	if (this->get_size() != 0) {
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
	if (this->get_size() != 0) {
		auto* iterator = this->create_sft_iterator();
		while (iterator->has_next())
		{
			values.push_back(iterator->next()->value);
		}
	}
	return values;
}