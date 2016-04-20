//
//  node.hpp
//  bin_search_tree
//
//  Created by Yonatan Yeshanov on 21.2.2016.
//  Copyright © 2016 Yonatan Yeshanov. All rights reserved.
//

#ifndef bin_search_tree_hpp
#define bin_search_tree_hpp

#include <stdio.h>

using std::cout;
using std::endl;

namespace tree {
    
    template <class key, class value>
    class NODE {
        key* _key;
        value* _value;
//        NODE<key,value>* _father;
        NODE<key,value>* _left;
		NODE<key,value>* _right;
        
    public:
        NODE<key,value>(const key& k, const value& v,
        		NODE* father = NULL, NODE* left = NULL, NODE* right = NULL) :
        	_key(new key(k)), _value(new value(v)), /*_father(father),*/ _left(left), _right(right){}
        NODE<key,value>(NODE& node) = delete;
        ~NODE<key,value>(){ delete _key; delete _value; }
//        void set_father(NODE* father) { _father = father; }
        void set_left(NODE* left) { _left = left; }
        void set_right(NODE* right) { _right = right; }
        void set_pair(const key& k, const value& v) { *(_key) = k; *(_value) = v; }
//        NODE* get_father() { return _father; }
        NODE* get_left() { return _left; }
        NODE* get_right() { return _right; }
        key& get_key() { return *_key; }
        value& get_value() { return *_value; }
        NODE& operator=(const NODE&) = delete;
    };
    
}

#endif /* bin_search_tree_hpp */
