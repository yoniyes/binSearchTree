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
        USE OF THE "TREE" CLASS IS ONLY PERMITTED WITH COMPARISON OPERATORS OVERLOADING.
     **/
    
    template <class key, class value>
    class TREE {

    	/*
    	 * Fields.
    	 */
        NODE<key, value>* _root;
        int _size;

        /**
         * Print the tree.
         */
        class printNode {
        public:
        	void operator()(NODE<key,value>* node, int depth) {
        		for (int i = 1; i < depth; i++) {
        			cout << "	";
       			}
       			cout << node->get_key() << endl;
       		}
      	};

        /*
         * Find method.
         */
        NODE<key, value>* find(const key& k){
        	NODE<key, value>* current = this->_root;
        	return this->find_aux(k, current);
        }
        NODE<key, value>* find_aux(const key& k, NODE<key, value>* current) {
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
        
        // For copy constructor.
        NODE<key,value>* copy_tree(NODE<key,value>* node) {
        	if (!node) {
        		return NULL;
        	}
        	NODE<key,value>* copy = new NODE<key,value>(node->get_key(),
        			node->get_value());
        	NODE<key,value>* left_copy = copy_tree(node->get_left());
        	NODE<key,value>* right_copy = copy_tree(node->get_right());
        	copy->set_left(left_copy);
        	copy->set_right(right_copy);
        	return copy;
        }

        void delete_tree(NODE<key,value>* node) {
        	if (!node) {
        		return;
        	}
        	delete_tree(node->get_left());
        	delete_tree(node->get_right());
        	delete node;
        }

    public:
        TREE<key,value>() : _root(NULL), _size(0) {}
        TREE<key,value>(TREE& tree) {
        	// Using pre-order.
        	_root = copy_tree(tree.get_root());
        	_size = tree.get_size();
        }
        ~TREE<key,value>() {
        	// Using post-order.
        	delete_tree(get_root());
        }
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

        //TODO: create remove().
        void remove(const key& k);
        int get_size() { return _size; }
        void set_root(NODE<key, value>* new_root) { _root = new_root; }
        NODE<key, value>* get_root() { return _root; }


        void printTree() {
        	cout << endl;
        	travel<printNode>();
        	cout << endl;
        }

        template <class functor>
        void travel() {
        	NODE<key,value>* node = get_root();
        	int depth = 0;
        	travel_aux<functor>(node, depth);
        }
        /**
         * In-order.
         * Depth will be incremented to tell functor the level
         * we're in the tree.
         */
        template <class functor>
        void travel_aux(NODE<key,value>* node, int depth) {
        	if (!node) {
        		return;
        	}
        	depth++;
        	travel_aux<functor>(node->get_left(), depth);
        	functor()(node, depth);
        	travel_aux<functor>(node->get_right(), depth);
        }
    };
}


#endif /* tree_hpp */
