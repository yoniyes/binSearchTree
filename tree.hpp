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

	//Exceptions.
	class EmptyTree {};
	class NotInTree {};

    /**
        USE OF THIS CLASS IS ONLY PERMITTED WITH COMPARISON OPERATORS OVERLOADING.
     **/
    
    template <class key, class value>
    class TREE {

    	/*
    	 * Fields.
    	 */
        NODE<key, value>* _root;
        int _size;

        /*
         * Find method.
         */
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
            if (current->get_key() > k) {
                if (current->get_left() == NULL) {
                    return current;
                }
                return this->find_aux(k, current->get_left());
            } else if (current->get_key() < k) {
                if (current->get_right() == NULL) {
                    return current;
                }
                return this->find_aux(k, current->get_right());
            } else {
                return current;
            }
        };       //For get,insert,remove.
        
    public:
        TREE<key,value>() : _root(NULL), _size(0){}
        TREE<key,value>(TREE& tree) = default;  //Maybe later with SIYUR?
        ~TREE<key,value>() = default;           //Maybe later with SIYUR?
        //TODO: NEEDS TO BE TESTED.
        value get(const key& k){
        	NODE<key,value>* temp = find(k);
        	if (!temp) {
        		throw EmptyTree();
        	} else if (temp->get_key() == k) {
        		return temp->get_value();
        	}
        	throw NotInTree();
        }

        //insert() returns true if key already existed and false if it is a new key.
        bool insert(const key& k, const value& v){
        	if (!get_root()) {
        		set_root(new NODE<key,value>(k,v));
        		_size++;
        		return false;
        	}
        	NODE<key,value>* temp = find(k);
        	if (temp->get_key() == k){
        		temp->set_pair(k,v);
        		return true;
        	}
        	if (temp->get_key() > k) {
        		temp->set_left(new NODE<key,value>(k,v));
        	} else {
        		temp->set_right(new NODE<key,value>(k,v));
        	}
        	_size++;
        	return false;
        }

        void remove(const key& k);
        int get_size() { return _size; }
        void set_root(NODE<key, value>* new_root) { _root = new_root; }
        NODE<key, value>* get_root() { return _root; }
    };
    
}



#endif /* tree_hpp */
