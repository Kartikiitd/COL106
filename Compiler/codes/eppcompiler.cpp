/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line


// #include <iostream>
// using namespace std;
void postorder(ExprTreeNode * root,Parser &targ , vector<string> &out){
    // cout<<"postorder called"<<endl;
    if(root == NULL){
        return ;
    }
    else if(root->id ==":=" && root->left != NULL && root->left->type =="VAR"){
        postorder(root->right,targ ,out);
        int id = targ.symtable->search(root->left->id);
        out.push_back("mem["+to_string(id)+"] = POP");
        return;
    }
    else if(root->id ==":=" && root->left != NULL && root->left->type =="RET"){
        postorder(root->right,targ ,out);
        out.push_back("RET = POP");
        return;
    }
    if(root->left != NULL && root->left->type =="DEL"){
        int id = targ.symtable->search(root->right->id);
        out.push_back("DEL = mem["+to_string(id)+"]");
        return;
    }
    
    if(root->id == ":="){
        return;
    }
    postorder(root->right,targ,out);
    postorder(root->left,targ,out);
    if(root->type =="VAL"){
        out.push_back("PUSH "+root->id);
    }
    if(root->type =="VAR"){
        int id = targ.symtable->search(root->id);
        out.push_back("PUSH mem["+to_string(id)+"]");
    }
    if(root->type =="ADD" || root->type =="SUB" || root->type =="DIV" || root->type =="MUL"){
        out.push_back(root->type);
    }
    
    // cout<<"postorder done"<<endl;
    return;
    
}
EPPCompiler::EPPCompiler(){

}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size = mem_limit;
    output_file = out_file;
    for(int i=0;i<mem_limit;i++){// allot the index = i if v[i]==-2 and change v[i] to i;
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(vector<vector<string> > code){
    for(int i=0;i<code.size();i++){
        targ.parse(code[i]);
        // cout<<"parse done"<<endl;
        ExprTreeNode* t = targ.expr_trees[i];
        if(t->left->type == "VAR" ){
            targ.symtable->assign_address(t->left->id,mem_loc[mem_loc.size()-1]);
            mem_loc.pop_back();
        }
        
        // cout<<"reached here"<<endl;
        vector<string> temp = generate_targ_commands();
        if(t->left->type == "DEL"){
            int idfree = targ.symtable->search(t->right->id);
            if(idfree != -2){
                mem_loc.push_back(idfree);
            }
            targ.symtable->remove(t->right->id);
        }
        // cout<< " reched here too"<<endl;
        write_to_file(temp);
        // cout <<"to the end"<<endl;
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> out ;
    postorder(targ.expr_trees[targ.expr_trees.size()-1],targ,out);
    return out;
}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream out_file;
    out_file.open(output_file,ios::app);
    for (int i = 0 ; i<commands.size() ; i++){
        out_file<<commands[i]<<endl;
    }
    out_file.close();
}

EPPCompiler::~EPPCompiler(){
    delete targ.symtable;
}
/*
//remove these before submission
#include <iostream>
using namespace std;

int main(){
    EPPCompiler epp("output.txt",100);
    vector<vector<string> > code;
    vector<string> line1;
    line1.push_back("p");
    line1.push_back(":=");
    line1.push_back("(");
    line1.push_back("1");
    line1.push_back("+");
    line1.push_back("(");
    line1.push_back("2");
    line1.push_back("*");
    line1.push_back("3");
    line1.push_back(")");
    line1.push_back(")");
    code.push_back(line1);
    vector<string> line2;
    line2.push_back("q");
    line2.push_back(":=");
    line2.push_back("(");
    line2.push_back("p");
    line2.push_back("+");
    line2.push_back("1");
    line2.push_back(")");
    code.push_back(line2);
    vector<string> line3;
    line3.push_back("r");
    line3.push_back(":=");
    line3.push_back("(");
    line3.push_back("q");
    line3.push_back("+");
    line3.push_back("1");
    line3.push_back(")");
    code.push_back(line3);
    vector<string> line4;
    line4.push_back("del");
    line4.push_back(":=");
    line4.push_back("r");
    code.push_back(line4);
    vector<string> line5;
    line5.push_back("ret");
    line5.push_back(":=");
    line5.push_back("p");
    code.push_back(line5);

    // for (int i = 0 ; i<code.size() ; i++){
    //     for (int j = 0 ; j<code[i].size() ; j++){
    //         cout<<code[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout<<"hello"<<endl;
    epp.compile(code);
    // cout<<"heu"<<endl;
    // vector<string> commands2 = epp.generate_targ_commands();
    // for (int i = 0 ; i<commands1.size() ; i++){
    //     cout<<commands1[i]<<endl;
    // }
    // epp.write_to_file(commands2);
    return 0;
}
*/