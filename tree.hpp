//
//  tree.hpp
//  bin_search_tree
//
//  Created by Yonatan Yeshanov on 21.2.2016.
//  Copyright © 2016 Yonatan Yeshanov. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include "node.hpp"

namespace tree {
    
    template <class key, class value>
    class TREE {
        NODE<key, value>* _root;
        int _size;
        
        /**
            USE OF THIS METHOD IS ONLY PERMITTED WITH <, > OVERLOADING.
         **/
        NODE<key, value>* find(const key& k){
        	NODE<key, value>* current = this->_root;
        	return this->find_aux(k, current);
        }
        NODE<key, value>* find_aux(const key& k, NODE<key, value>* current){
            //Check if ended a path.
            if (current == NULL) {
                return NULL;
            }

            //If key is smaller, go left. If key is bigger, go right.
            //Otherwise, return current node.
            if (*(current->_key) > k) {
                if (current->_left == NULL) {
                    return current;
                }
                return this->find_aux(k, current->_left);
                //return current->_left->find_aux(k);
            } else if (*(current->_key) < k) {
                if (current->_right == NULL) {
                    return current;
                }
                return this->find_aux(k, current->_right);
                //return this->_right->find(k);
            } else {
                return current;
            }
        };       //For get,insert,remove.
        
    public:
        TREE<key,value>() : _root(NULL), _size(0){}
        TREE<key,value>(TREE& tree) = default;  //Maybe later with SIYUR?
        ~TREE<key,value>() = default;           //Maybe later with SIYUR?
        const value& get(const key& k);
        bool insert(const key& k, const value& v);
        void remove(const key& k);
        int get_size() { return _size; }
        void set_root(NODE<key, value>* new_root) { _root = new_root; }
        NODE<key, value>* get_root() { return _root; }
    };
    
}



#endif /* tree_hpp */
