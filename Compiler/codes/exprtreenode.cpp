/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    this->id = "";
    this->left = NULL;
    this->right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    this->left = NULL;
    this->right = NULL;
    //if t is of type VAL do store the val as v;
    // if t type VAR store the var;
    if(t=="ret"){
        this->type = "RET";
        this->id = t;
        this->num = 0;
    }
    else if( t=="+" || t=="-" || t=="*" || t=="/"){
        this->id = t;
        this->num = 0;
        if(t=="+"){
            this->type = "ADD";
        }
        if(t=="-"){
            this->type = "SUB";
        }
        if(t=="*"){
            this->type = "MUL";
        }
        if(t=="/"){
            this->type = "DIV";
        }
    }
    else if(t==":="){
        this->type = "EQUAL";//this is defined by me;
        this->id=t;
        this->num = 0;
    }
    else if(t=="del"){
        this->type = "DEL";
        this->id =t;
        this->num =0;
    }
    else if(isdigit(t[0])){
        this->type = "VAL";
        this->id =t;
        this->num = stoi(t);
    }
    else{
        this->type= "VAR";
        this->id= t;
        this->num= 0;    }
    
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right;

}

