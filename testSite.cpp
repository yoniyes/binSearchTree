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
using namespace tree;

//Checks creation of tree and node.
//Checks set and get methods for node.
bool test1(){
	bool res = true;
	TREE<int,string> tr;
	TEST_EQUALS(res,tr.get_root(),NULL);
	TEST_EQUALS(res,tr.get_size(),0);
	//Node methods should ONLY be used in tree.hpp.
	NODE<int,string> node(0,"zero");
	std::cout << std::endl << node.get_key() << ", " << node.get_value() << std::endl;
	node.set_pair(1,"one\n");
	std::cout << node.get_key() << ", " << node.get_value() << std::endl;
	return res;
}

int main(){
	RUN_TEST(test1);
	return 0;
}
