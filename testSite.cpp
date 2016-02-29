//
//  testSite.cpp
//  bin_search_tree
//
//  Created by Yonatan Yeshanov on 21.2.2016.
//  Copyright © 2016 Yonatan Yeshanov. All rights reserved.
//

#include <iostream>
#include "tree.hpp"
#include "node.hpp"
#include "testsMacros.h"

using std::string;
using std::cout;
using std::endl;
using namespace tree;

//TODO: create a "tree-printing-function".

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
	//Test set_root for tree.
	tr.set_root(&node);
	TEST_EQUALS(res,&node,tr.get_root());
	return res;
}

//Tests if insert() puts new (and already existing) keys and values in the right place.
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
	tr.printTree();

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

int main(){
	RUN_TEST(testNode);
	RUN_TEST(testInsert1);
	RUN_TEST(testInsert2);
	return 0;
}
