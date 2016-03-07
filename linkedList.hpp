/*
 * linkedList.hpp
 *
 *  Created on: 7 במרץ 2016
 *      Author: yonatanyeshanov
 */

#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <cstdlib>

template <class T>
class listNode {

	T* _data;
	listNode<T>* _next;

public:
	listNode<T>() : _data(new T), _next(NULL) {}
	listNode<T>(T& data) : _data(new T(data)), _next(NULL) {}
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

public:
	linkedList<T>() : _head(new listNode<T>()), _size(0) {}
	linkedList<T>(linkedList& list) : _head(NULL), _size(0) {
		//TODO: write list copy constructor.
	}
	~linkedList() {
		//TODO: write list destructor.
	}

	// Insert to start of list.
	void insert_first(const T& data) {
		listNode<T> node(data);
		node.set_next(_head->get_next());
		_head->set_next(&node);
		_size++;
	}
	// Insert to end of list.
	void insert_last(const T& data) {
		listNode<T>* node = get_head();
		while (node->get_next()) {
			node = node->get_next();
		}
		node->set_next(listNode<T>(data));
		_size++;
	}
	// Insert after a node.
	void insert_after(listNode<T>* node, const T& data) {
		listNode<T>* to_insert = new listNode<T>(data);
		to_insert->set_next(node->get_next());
		node->set_next(to_insert);
		_size++;
	}
	listNode<T>* find(T& data) {
		listNode<T>* node = get_head();
		while (node->get_next()) {
			node = node->get_next();
			if (node->get_data() == data) {
				return node;
			}
		}
		return NULL;
	}
	void remove(listNode<T>& node) {
		//TODO: write remove().
	}
	listNode<T>* get_head() { return _head; }
	listNode<T>* get_first() { return _head->get_next(); }
	int get_size() { return _size; }
};


#endif /* LINKEDLIST_HPP_ */
