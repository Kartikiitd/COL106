/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"

//Write your code below this line

// using namespace std;
// #include <iostream>//remove all these before submission
// #include <vector>


Parser::Parser(){
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression){
    ExprTreeNode * root = new ExprTreeNode(":=",0);
    expr_trees.push_back(root);
    ExprTreeNode * curr = new ExprTreeNode(expression[0],0);
    root->left = curr;
    if(curr->type == "VAR"){//insertion of new var in symtable
        if(symtable->search(curr->id)==-2){
            symtable->insert(curr->id);
        }
    }
    if(expression[0] =="del"){
        root->right = new ExprTreeNode(expression[2],0);//delete has only three tokens
        //update the symtable accordingly
        return;
    }
    vector<ExprTreeNode*> stack;
    int si = expression.size();
    for(int i=2 ; i<si ; i++){
        string te = expression[i];
        if(te =="("){
            continue;
        }
        if(te !="(" && te!=")"){
        ExprTreeNode * curr = new ExprTreeNode(te,0);
        stack.push_back(curr);
        // cout<<stack.size()<<endl;
        if(curr->type == "VAR"){//insertion of new var in symtable
            if(symtable->search(curr->id)==-2){
                symtable->insert(curr->id);
            }
        }
        }
        if(te == ")"){
            ExprTreeNode *t1 = stack[stack.size()-1];
            ExprTreeNode *t2 = stack[stack.size()-2];
            ExprTreeNode *t3 = stack[stack.size()-3];
            t2->left = t3;
            t2->right = t1;
            stack.pop_back();
            stack.pop_back();
            stack.pop_back();
            stack.push_back(t2);
            // cout<<stack.size()<<endl;
        } 
        
    }
    
    root->right = stack[0];
    
    return;
}

Parser::~Parser(){
    delete symtable;// check the destructor before submission
}
// void display(ExprTreeNode * root){
//     if(root==NULL){
//         return;
//     }
//     display(root->left);
//     cout<<root->id<<" ";
//     display(root->right);
//     return;
// }
// void display1(SymNode *root){
//     if(root==NULL){
//         return;
//     }
//     display1(root->left);
//     cout<<root->key<<" ";
//     display1(root->right);
//     return;
// }

/* #include <iostream>
using namespace std;
int main(){
    Parser *S = new Parser();
    vector<string> ex ;
    vector<string> ex2 ;
    string elements2[]= {"ret", ":=", "(", "a", "x", "(", "b", "+", "c", ")", ")"};
    int numElements2 = sizeof(elements2) / sizeof(elements2[0]);

    for (int i = 0; i < numElements2; i++) {
        ex2.push_back(elements2[i]);
        // cout<<ex[i]<<" ";
    }
    string elements[] = {"del" , ":=" , "a"};
    int numElements = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < numElements; i++) {
        ex.push_back(elements[i]);
        // cout<<ex[i]<<" ";
    }
    S->parse(ex2);
    // cout<<S->symtable->get_root()->key<<endl;
    // cout<<endl;
    S->parse(ex);
    // cout<<S->symtable->get_root()->key<<endl;
    vector<string> ex1;
    string elements1[] = {"d",":=","(","2","+","(","7","x","a",")",")"};
    int numElements1 = sizeof(elements1) / sizeof(elements1[0]);

    for (int i = 0; i < numElements1; i++) {
        ex1.push_back(elements1[i]);
        // cout<<ex[i]<<" ";
    }
    // cout<<S->symtable->get_size()<<endl;
    // cout<<S->symtable->get_root()->key<<endl;
    // cout<<"hello"<<endl;
    S->parse(ex1);
    // cout<<S->expr_trees.size()<<endl;
    // display(S->expr_trees[0]);
    // cout<<endl;
    // display(S->expr_trees[1]);
    // cout<<endl;
    // display(S->expr_trees[2]);
    // cout<<endl;
    cout<<S->symtable->get_size()<<endl;
    cout<<S->symtable->get_root()->key<<endl;
    display1(S->symtable->get_root());
    cout<<endl;
    delete S;
    return 0;
}
 *//* 
void pot(ExprTreeNode * now){
    if(now->left!=NULL){
            pot(now->left);
    }
    if(now->right!=NULL){
            pot(now->right);
    }
    cout<<now->id<<","<<flush;
}
int main(){

    Parser *p=new Parser();
    vector<string> input;

    while(true){
        bool inpu=true;
        bool end=false;
        while(inpu){
            string x;
            cin>>x;
            if(x=="!"){
                break;
            }
            else if(x=="?"){
                end=true;
                break;
            }
            else{
                input.push_back(x);
            }

        }
        if(end){
            //p.parse(input);
            break;
        }
        p->parse(input);
        input.clear();
        
    }

    

    for(int i=0;i<p->expr_trees.size();i++){
        cout<<"now showing " <<p->expr_trees[i]->left->id<<endl;
        pot(p->expr_trees[i]);
        cout<<endl;

    }
    

    delete p;
    
    return 0;

} */