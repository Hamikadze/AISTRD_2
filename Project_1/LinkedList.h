#pragma once
#include <stdexcept>
#include <iostream>
#include "Iterator.h"

template <class  T>
class LinkedList {
public:
	class Node
	{
	public:
		Node(T data, Node * next = nullptr/*, Node * prev = nullptr*/) {
			this->data = data;
			this->next = next;
			//this->prev = prev;
		};
		~Node()
		{
			next = nullptr;
			delete next;
			//prev = nullptr;
			//delete prev;
			data = {};
		};
		T data;
		Node* next;
		//Node* prev;
	};
	void add_first(T newElem);
	void reset_list();
	Node * head{};
	Node * tail{};
	size_t size;
	class ListIterator : public LIterator<T>
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
	void pop_back(); // удаление последнего элемента
	void pop_front(); // удаление первого элемента
	void insert(size_t index, T newElem); // добавление элемента по индексу
	T at(size_t index) const;
	void remove(size_t index); // удаление элемента по индексу
	size_t get_size() const;
	void print_to_console() const; // вывод элементов списка в консоль через разделитель, не использовать at
	void clear(); // удаление всех элементов списка
	void set(size_t index, T newElem) const; // замена элемента по индексу на передаваемый элемент
	bool isEmpty() const; // проверка на пустоту списка
	bool contains(LinkedList* list) const; // проверка на содержание другого списка в списке
	bool contains(T data) const;
	bool equals(LinkedList* list) const;

	LIterator<T>* create_list_iterator() const;
	friend std::ostream& operator<<(std::ostream& os, const LinkedList<T>& linked_list) {
		if (linked_list.size == 0)
			return os << "[nullptr]";
		auto* list = linked_list.create_list_iterator();
		os << "[nullptr] <- ";
		while (list->has_next()) {
			os << "[" << list->next() << "] <- ";
		}
		os << "[nullptr]" << std::endl;
		return os;
	};
};
