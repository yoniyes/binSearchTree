//
//  testSite.cpp
//  bin_search_tree
//
//  Created by Yonatan Yeshanov on 21.2.2016.
//  Copyright © 2016 Yonatan Yeshanov. All rights reserved.
//

#include <iostream>
#include <utility>
#include "tree.hpp"
#include "node.hpp"
#include "linkedList.hpp"
#include "testsMacros.h"

using std::string;
using std::cout;
using std::endl;
using std::pair;
using namespace tree;

//Checks creation of tree and node.
//Checks set and get methods for node and tree.
//Node methods should ONLY be used in tree.hpp.

bool testNode(){
	bool res = true;
	TREE<int,string> tr;
	TEST_EQUALS(res,tr.get_root(),NULL);
	TEST_EQUALS(res,tr.get_size(),0);
	NODE<int,string> node(0,"zero");
	TEST_EQUALS(res,0,node.get_key());
	TEST_EQUALS(res,"zero",node.get_value());
	node.set_pair(1,"one\n");
	TEST_EQUALS(res,1,node.get_key());
	TEST_EQUALS(res,"one\n",node.get_value());
	TEST_EQUALS(res,NULL,node.get_left());
	TEST_EQUALS(res,NULL,node.get_right());
	NODE<int,string> node_l(0,"zero");
	node.set_left(&node_l);
	node.set_right(&node_l);
	TEST_EQUALS(res,&node_l,node.get_left());
	TEST_EQUALS(res,&node_l,node.get_right());
	return res;
}

//Tests if insert() puts new (and already existing) keys and values in the right place.
//Test copy constructor.
bool testInsert1(){
	bool res = true;
	TREE<int,string> tr;
	TEST_EQUALS(res, tr.get_size(), 0);
	tr.insert(10, "ten");
	TEST_EQUALS(res, tr.get_size(), 1);
	TEST_EQUALS(res,tr.get_root()->get_key(),10);
	TEST_EQUALS(res,tr.get_root()->get_value(),"ten");
	tr.insert(6,"six");
	TEST_EQUALS(res, tr.get_size(), 2);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_key(),6);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_value(),"six");
	tr.insert(11,"eleven");
	TEST_EQUALS(res, tr.get_size(), 3);
	TEST_EQUALS(res,tr.get_root()->get_right()->get_key(),11);
	TEST_EQUALS(res,tr.get_root()->get_right()->get_value(),"eleven");
	tr.insert(7,"seven");
	TEST_EQUALS(res, tr.get_size(), 4);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_right()->get_key(),7);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_right()->get_value(),"seven");
	tr.insert(5,"five");
	TEST_EQUALS(res, tr.get_size(), 5);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_left()->get_key(),5);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_left()->get_value(),"five");
	tr.insert(10,"not ten");
	TEST_EQUALS(res, tr.get_size(), 5);
	TEST_EQUALS(res,tr.get_root()->get_key(), 10);
	TEST_DIFFERENT(res,tr.get_root()->get_value(),"ten");
	TEST_EQUALS(res,tr.get_root()->get_value(),"not ten");
	TREE<int,string> tr2(tr);
	TEST_DIFFERENT(res,tr.get_root(),tr2.get_root());
	TEST_EQUALS(res,tr.get_size(),tr2.get_size());
	TEST_EQUALS(res,tr.get_root()->get_key(),tr2.get_root()->get_key());
	TEST_EQUALS(res,tr.get_root()->get_value(),tr2.get_root()->get_value());

	return res;
}

//Test another case of insert().
bool testInsert2(){
	bool res = true;
	TREE<int,string> tr;
	TEST_EQUALS(res, tr.get_size(), 0);
	tr.insert(10, "ten");
	TEST_EQUALS(res, tr.get_size(), 1);
	TEST_EQUALS(res,tr.get_root()->get_key(),10);
	TEST_EQUALS(res,tr.get_root()->get_value(),"ten");
	tr.insert(6,"six");
	TEST_EQUALS(res, tr.get_size(), 2);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_key(),6);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_value(),"six");
	tr.insert(8,"eight");
	TEST_EQUALS(res, tr.get_size(), 3);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_right()->get_key(),8);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_right()->get_value(),"eight");
	tr.insert(7,"seven");
	TEST_EQUALS(res, tr.get_size(), 4);
	TEST_EQUALS(res,tr.get_root()->get_left()->get_right()->get_left()->get_key(),7);
	TEST_EQUALS(res,
			tr.get_root()->get_left()->get_right()->get_left()->get_value(),"seven");
	TEST_FALSE(res,tr.get_root()->get_right());

	return res;
}

bool testGet(){
	bool res = true;
	TREE<int,string> tr;
	try {
		TEST_EQUALS(res,"ten",tr.get(10));
	} catch (EmptyTree& e) {
		cout << "CAUGHT! ";
	}
	tr.insert(10, "ten");
	tr.insert(6,"six");
	tr.insert(8,"eight");
	tr.insert(7,"seven");
	TEST_EQUALS(res,"ten",tr.get(10));
	TEST_EQUALS(res,"six",tr.get(6));
	TEST_EQUALS(res,"seven",tr.get(7));
	TEST_EQUALS(res,"eight",tr.get(8));
	tr.insert(11,"eleven");
	TEST_EQUALS(res,"eleven",tr.get(11));
	try {
		TEST_EQUALS(res,"ten",tr.get(1));
	} catch (NotInTree& e) {
		cout << "CAUGHT! ";
	}

	return res;
}

bool testRemove() {
	bool res = true;
	TREE<int,string> tr;
	tr.insert(10, "ten");
	tr.insert(6,"six");
	tr.insert(8,"eight");
	tr.insert(7,"seven");
	tr.insert(5,"five");
	tr.insert(20,"twenty");
	tr.insert(15,"fifteen");
	tr.insert(21,"twenty one");
	tr.printTree();
	tr.remove(10);
	tr.printTree();

	TREE<int,string> tr2;
	tr2.insert(3,"three");
	try {
		tr2.remove(1);
	} catch (NotInTree& e) {
		cout << "CAUGHT! ";
	}
	tr2.remove(3);
	try {
		tr2.remove(3);
	} catch (NotInTree& e) {
		cout << "CAUGHT! ";
	}
	tr2.insert(1,"1");
	tr2.insert(2,"2");
	tr2.insert(3,"3");
	tr2.insert(4,"4");
	tr2.printTree();
	tr2.remove(1);
	tr2.printTree();
	tr2.remove(2);
	tr2.printTree();
	tr2.remove(3);
	tr2.printTree();

	return res;
}

class compareInt {
public:
	bool operator()(const int first, const int second) const {
		return first <= second;
	}
};

bool testList() {
	bool res = true;
	//Test creation.
	linkedList<int> l;
	TEST_EQUALS(res, l.get_size(), 0);
	TEST_EQUALS(res,l.get_first(), NULL);
	//Test insertion.
	l.insert(10);
	TEST_EQUALS(res, l.get_size(), 1);
	l.insert(9);
	TEST_EQUALS(res, l.get_size(), 2);
	l.insert(11);
	TEST_EQUALS(res, l.get_size(), 3);
	l.insert(-23);
	TEST_EQUALS(res, l.get_size(), 4);
	l.insert_after(l.get_head(), -1);
	TEST_EQUALS(res, l.get_size(), 5);
	listNode<int>* ptr = l.find(1);
	TEST_EQUALS(res, ptr, NULL);
	ptr = l.find(9);
	TEST_DIFFERENT(res, ptr, NULL);
	TEST_EQUALS(res, ptr->get_next()->get_data(), 11);
	l.printList();
	ptr->set_data(7);
	l.printList();
	l.insert_after(ptr, 30);
	TEST_EQUALS(res, l.get_size(), 6);
	l.printList();
	ptr = l.find(-23);
	l.insert_after(ptr, 12);
	TEST_EQUALS(res, l.get_size(), 7);
	l.printList();
	l.remove(l.find(7));
	TEST_EQUALS(res, l.get_size(), 6);
	l.printList();
	l.remove(l.find(1));
	TEST_EQUALS(res, l.get_size(), 6);
	l.printList();
	linkedList<int> l2(l);
	TEST_EQUALS(res, l2.get_size(), 6);
	l2.printList();
	l2.sort(compareInt());
	l2.printList();
	return res;
}

void printPairs(listNode<pair<int,string>>* node) {
	cout << endl;
	for (listNode<pair<int,string>>* curr = node; curr; curr = curr->get_next()) {
		cout << curr->get_data().first << "	";
	}
	cout << endl;
}

bool testExport() {
	bool res = true;
	TREE<int,string> tr;
	tr.insert(10, "ten");
	tr.insert(6,"six");
	tr.insert(8,"eight");
	tr.insert(7,"seven");
	tr.insert(5,"five");
	tr.insert(20,"twenty");
	tr.insert(15,"fifteen");
	tr.insert(21,"twenty one");
	tr.printTree();
	linkedList<pair<int,string>>* l = tr.export_inorder();
	TEST_EQUALS(res,l->get_size(),8);
	TEST_EQUALS(res,l->get_first()->get_data().first,5);
	TEST_EQUALS(res,l->get_first()->get_data().second,"five");
	printPairs(l->get_first());
	return res;
}

int main(){
	RUN_TEST(testNode);
	RUN_TEST(testInsert1);
	RUN_TEST(testInsert2);
	RUN_TEST(testGet);
	RUN_TEST(testRemove);
	RUN_TEST(testList);
	RUN_TEST(testExport);
	return 0;
}
