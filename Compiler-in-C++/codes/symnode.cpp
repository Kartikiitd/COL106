/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line

SymNode::SymNode(){

}

SymNode::SymNode(string k){
    key = k;
    height = 1;
}

SymNode* SymNode::LeftLeftRotation(){
    return NULL;
}

SymNode* SymNode::RightRightRotation(){
    return NULL;
}

SymNode* SymNode::LeftRightRotation(){
    return NULL;
}

SymNode* SymNode::RightLeftRotation(){
    return NULL;
}

SymNode::~SymNode(){
    delete left;
    delete right;

    // define according to usage
}