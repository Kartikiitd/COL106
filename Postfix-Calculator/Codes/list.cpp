#include <iostream>
using namespace std;
#include "node.h"
#include "list.h"
/* PART B */
/* Stacks using Linked Lists */

/* 
Linked Lists with Sentinels 
[X]<->[7]<->[3]<->[2]<->[X]
The head and tails are dummy elements ([X]) that do not have valid values.
These are called sentinel elements.
*/

// class List {
// private: 
//     int size;
//     Node* sentinel_head;
//     Node* sentinel_tail;

// public: 
    List::List(){
        size = 0;
        try{
        sentinel_head = new Node(1);}
        catch(const bad_alloc& e){
            throw runtime_error("Out of Memory");
        }
        try{
        sentinel_tail = new Node(1);}
        catch(const bad_alloc& e){
            throw runtime_error("Out of Memory");
        }
        sentinel_head ->next = sentinel_tail;
        sentinel_tail ->prev = sentinel_head;
    }

    List::~List(){
        if(size !=0){
            Node *temp = sentinel_head->next;
            while(!temp->is_sentinel_node()){
                temp=temp->next;
                delete temp->prev;
            }
            delete temp;
        }
        else{
        delete sentinel_head;
        delete sentinel_tail;
        }
    }

    // Insert an element at the tail of the linked list 
    void List::insert(int v){
        
        Node *temp = sentinel_tail->prev;
        try{
        Node *n= new Node(v,sentinel_tail,temp);
        sentinel_tail->prev = n;
        n->prev->next=n;
        size +=1;}
        catch(const bad_alloc& e){
            throw runtime_error("Out of Memory");
        }
    }

    // Delete the tail of the linked list and return the value
    // You need to delete the valid tail element, not the sentinel
    int List::delete_tail(){
        Node *temp = sentinel_tail->prev;
        int valueof = temp->get_value();
        sentinel_tail->prev = sentinel_tail->prev->prev;
        sentinel_tail->prev->next = sentinel_tail;
        delete temp;
        size -=1;
        return valueof;
    }

    // Return the size of the linked list 
    // Do not count the sentinel elements
    int List::get_size(){
        return size;
    }

    // Return a pointer to the sentinel head of the linked list 
    Node* List::get_head(){
        return sentinel_head;
    }

