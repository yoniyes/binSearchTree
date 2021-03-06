/*
 * linkedList.hpp
 *
 *  Created on: 7 במרץ 2016
 *      Author: yonatanyeshanov
 */

#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <cstdlib>

using std::cout;
using std::endl;

template <class T>
class listNode {

	T* _data;
	listNode<T>* _next;

public:
	listNode<T>() : _data(new T), _next(NULL) {}
	listNode<T>(const T& data) : _data(new T(data)), _next(NULL) {}
	~listNode<T>() { delete _data; }
	listNode<T>(listNode<T>& node) : _data(new T(node.get_data())), _next(NULL) {}
	listNode<T>& operator=(const listNode<T>&) = delete;

	 const T& get_data() { return *_data; }
	 void set_data(const T& data) {
		 if (_data) {
			 delete _data;
		 }
		 _data = new T(data);
	 }
	 listNode<T>* get_next() { return _next; }
	 void set_next(listNode<T>* next) { _next = next; }
};


template <class T>
class linkedList {

	// Dummy node - points to the first node.
	listNode<T>* _head;
	int _size;

	listNode<T>* copy_node(listNode<T>* node) {
		if (!node) {
			return NULL;
		}
		listNode<T>* one = new listNode<T>(node->get_data());
		listNode<T>* two = copy_node(node->get_next());
		one->set_next(two);
		return one;
	}

public:
	linkedList<T>() : _head(new listNode<T>()), _size(0) {}
	linkedList<T>(linkedList& list) : _head(new listNode<T>()),
			_size(list.get_size()) {
		listNode<T>* node = list.get_first();
		_head->set_next(copy_node(node));
	}
	~linkedList() {
		listNode<T>* current = get_head();
		while (current) {
			listNode<T>* to_remove = current;
			current = current->get_next();
			delete to_remove;
		}
	}

	// Insert to end of list.
	void insert(const T& data) {
		listNode<T>* node = get_head();
		while (node->get_next()) {
			node = node->get_next();
		}
		node->set_next(new listNode<T>(data));
		_size++;
	}
	// Insert after a node.
	void insert_after(listNode<T>* node, const T& data) {
		listNode<T>* to_insert = new listNode<T>(data);
		to_insert->set_next(node->get_next());
		node->set_next(to_insert);
		_size++;
	}

	// Assertion: each node has unique data (because the use of this list is
	// for exporting a binSearchTree to it using <key,value> pairs which are
	// unique in a dictionary).
	listNode<T>* find(const T& data) {
		listNode<T>* node = get_head();
		while (node->get_next()) {
			node = node->get_next();
			if (node->get_data() == data) {
				return node;
			}
		}
		return NULL;
	}

	//TODO: make it merge-sort and NOT bubble-sort.
	template <class COMPARATOR>
	void sort(const COMPARATOR& compare) {
		if (get_size() <= 1) {
			return;
		}
		for (int i = 0; i < get_size(); i++) {
			for (listNode<T>* curr = get_first(); curr->get_next();
					curr = curr->get_next()) {
				listNode<T>* next = curr->get_next();
				if (!compare(curr->get_data(), next->get_data())) {
					T temp = curr->get_data();
					curr->set_data(next->get_data());
					next->set_data(temp);
				}
			}
		}
	}
	void remove(listNode<T>* node) {
		if (!node) {
			return;
		}
		listNode<T>* current = get_head();
		while (current->get_next() != node) {
			current = current->get_next();
		}
		current->set_next(node->get_next());
		delete node;
		_size--;
	}
	listNode<T>* get_head() { return _head; }
	listNode<T>* get_first() { return _head->get_next(); }
	int get_size() { return _size; }

	void printList() {
		listNode<T>* node = get_first();
		cout << endl;
		while (node) {
			cout << node->get_data() << "	";
			node = node->get_next();
		}
		cout << endl;
	}
};


#endif /* LINKEDLIST_HPP_ */
