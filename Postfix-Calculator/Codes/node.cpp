#include <iostream>
using namespace std;
#include "node.h"
    


    // Use to construct a sentinel node (see list.h)
    Node::Node(bool sentinal){
        is_sentinel=true;
        value = 0;
        next = NULL;
        prev = NULL;
    }  

    // Use to construct a regular node
    Node::Node(int v, Node* nxt, Node* prv){
        is_sentinel = false;
        value = v;
        next = nxt;
        prev = prv;
    }

    // Return whether a node is a sentinel node 
    // Use it to check if we are at the ends of a list
    bool Node::is_sentinel_node(){
        if(is_sentinel){
            return true;
        }
        return false;
    }

    // Return the value of a node
    int Node::get_value(){
        return value;
    }

