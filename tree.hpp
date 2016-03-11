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
#include "linkedList.hpp"
#include "node.hpp"

namespace tree {

using std::pair;

	/**
	 * Exceptions.
	 */
	class EmptyTree {};
	class NotInTree {};

    /**
     * USE OF THE "TREE" CLASS IS ONLY PERMITTED WITH COMPARISON OPERATORS OVERLOADING.
     */
    
    template <class key, class value>
    class TREE {

    	/**
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

        /**
         * Insert to list.
         */
        class insertToList {
        public:
        	void operator()(linkedList<pair<key,value>>* list, NODE<key,value>* node) {
        		pair<key,value> data(node->get_key(),node->get_value());
        		list->insert(data);
        	}
        };

        /**
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
        };
        
        /**
         * Helpers for remove()
         */
        NODE<key, value>* find_father(const key& k, NODE<key, value>* current) {
                    //Check if ended a path.
                    if (current == NULL) {
                        return NULL;
                    }
                    //If key is smaller, go left. If key is bigger, go right.
                    //Otherwise, return current node.
                    if (current->get_key() > k) {
                        if (current->get_left() == NULL) {
                            throw NotInTree();
                        } else if (current->get_left()->get_key() == k) {
                        	return current;
                        }
                        return find_father(k, current->get_left());
                    } else if (current->get_key() < k) {
                        if (current->get_right() == NULL) {
                            return current;
                        } else if (current->get_right()->get_key() == k) {
                        	return current;
                        }
                        return find_father(k, current->get_right());
                    } else {
                    	// If sent key is in root.
                    	return NULL;
                    }
        };

        bool remove_leaf(NODE<key,value>* to_remove, NODE<key,value>* father) {
        	if (!to_remove->get_left() && !to_remove->get_right()) {
        		//If the tree contains only one node.
        		if (!father) {
        			delete to_remove;
        			set_root(NULL);
        		} else {
        			if (father->get_left() == to_remove) {
        				father->set_left(NULL);
        			} else {
        				father->set_right(NULL);
        			}
        			delete to_remove;
        		}
        		_size--;
        		return true;
        	}
        	return false;
        }

        void remove_node(NODE<key,value>* to_remove, NODE<key,value>* father) {
        	// If has only one son.
        	// Left.
        	if (to_remove->get_left() && !to_remove->get_right()) {
        		if (to_remove == get_root()) {
        			set_root(to_remove->get_left());
        		} else if (father->get_left() == to_remove) {
        			father->set_left(to_remove->get_left());
        		} else {
        			father->set_right(to_remove->get_left());
        		}
        	//Right.
        	} else if (!to_remove->get_left() && to_remove->get_right()) {
        		if (to_remove == get_root()) {
        			set_root(to_remove->get_right());
        		} else if (father->get_left() == to_remove) {
        			father->set_left(to_remove->get_right());
        		} else {
        			father->set_right(to_remove->get_right());
        		}
        	}
        	// If has two sons.
        	else {
        		NODE<key,value>* to_swap = to_remove->get_right();
        		NODE<key,value> temp(to_remove->get_key(),to_remove->get_value());
        		while (to_swap->get_left()) {
        			to_swap = to_swap->get_left();
        		}
        		father = find_father(to_swap->get_key(), get_root());
        		to_remove->set_pair(to_swap->get_key(), to_swap->get_value());
        		to_swap->set_pair(temp.get_key(),temp.get_value());
        		to_remove = to_swap;
        		if (!father) {
        			set_root(to_remove->get_right());
        		} else if (father->get_left() == to_remove) {
        			father->set_left(to_remove->get_right());
        		} else {
        			father->set_right(to_remove->get_right());
        		}
        	}
        	delete to_remove;
        	_size--;
        	return;
        }

        /**
         * Helper for copy constructor.
         */
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

        /**
         * Helper for destructor.
         */
        void delete_tree(NODE<key,value>* node) {
        	if (!node) {
        		return;
        	}
        	delete_tree(node->get_left());
        	delete_tree(node->get_right());
        	delete node;
        }

        void set_root(NODE<key, value>* new_root) { _root = new_root; }

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

        /**
         * remove() workflow:
         * 1. Find the node that needs to be removed.
         * 2. If has no right/left son, let the father point accordingly instead.
         * 		Otherwise, go one step RIGHT and then all the way to the LEFT.
         * 		If has no sons (a leaf), skip step 3.
         * 3. Swap the two nodes.
         * 4. Remove the leaf which is now the node we wish to remove.
         */
        void remove(const key& k) {
        	NODE<key,value>* to_remove = find(k);
        	if (to_remove && to_remove->get_key() == k) {
        		NODE<key,value>* father = find_father(k, get_root());
        		// If it's a leaf.
        		if (!remove_leaf(to_remove,father)) {
        			remove_node(to_remove, father);
        		}
        		return;
        	}
        	throw NotInTree();
        }
        int get_size() { return _size; }
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


        //TODO: write export_inorder()
        linkedList<pair<key,value>>* export_inorder() {
        	linkedList<pair<key,value>>* l = new linkedList<pair<key,value>>();
        	in_order<insertToList>(l);
        	return l;
        }

        template <class functor>
        void in_order(linkedList<pair<key,value>>* l) {
        	NODE<key,value>* node = get_root();
        	in_order_aux<functor>(l, node);
        }

        template <class functor>
        void in_order_aux(linkedList<pair<key,value>>* l, NODE<key,value>* node) {
        	if (!node) {
        		return;
        	}
        	in_order_aux<functor>(l, node->get_left());
        	functor()(l, node);
        	in_order_aux<functor>(l, node->get_right());
        }
    };
}


#endif /* tree_hpp */
