#pragma once
#include <stdexcept>
#include <iostream>
#include "Iterator.h"

template <class  T>
class LinkedList {
	class Node
	{
		friend LinkedList<T>;
		Node(T data, Node* next = nullptr) {
			this->data = data;
			this->next = next;
		};
		~Node()
		{
			next = nullptr;
			delete next;
			data = {};
		};
		T data;
		Node* next;
	};
	void add_first(T newElem);
	void reset_list();
	void swap(Node*, Node*);
	void sortPart(int fromIndex, int toIndex, bool(*comp)(T, T));
	Node* at_node(size_t index) const;
	Node* head{};
	Node* tail{};
	size_t size;
	class ListIterator : public Iterator<T>
	{
	public:
		ListIterator(Node* head)
		{
			current = head;
		};

	private:
		T next() override;
		bool has_next() override;
		Node* current;
	};
public:
	LinkedList();
	~LinkedList();
	void push_back(T newElem);
	void push_front(T newElem);
	void pop_back(); // �������� ���������� ��������
	void pop_front(); // �������� ������� ��������
	void insert(size_t index, T newElem); // ���������� �������� �� �������
	T at(size_t index) const;
	void remove(size_t index); // �������� �������� �� �������
	size_t get_size() const;
	void print_to_console() const; // ����� ��������� ������ � ������� ����� �����������, �� ������������ at
	void clear(); // �������� ���� ��������� ������
	void set(size_t index, T newElem) const; // ������ �������� �� ������� �� ������������ �������
	void sort(bool (*comp)(T, T));
	bool isEmpty() const; // �������� �� ������� ������
	bool contains(LinkedList* list) const; // �������� �� ���������� ������� ������ � ������
	bool contains(T data) const;
	bool equals(LinkedList* list) const;

	Iterator<T>* create_list_iterator() const;

	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& linked_list) {
		if (linked_list.size == 0)
			return os << "[nullptr]";
		auto * list = linked_list.create_list_iterator();
		os << "[nullptr] <- ";
		while (list->has_next()) {
			os << "[" << list->next() << "] <- ";
		}
		os << "[nullptr]" << std::endl;
		return os;
	};
};
