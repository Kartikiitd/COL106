// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    left = NULL;
    right = NULL;
    count = 0;
    id = "";
    // Implement your function here    
}

Dict::Dict(string s)
{
    this->count=1;
    this->id = s;
    this->left = NULL;
    this->right = NULL;
}

int Height(Dict * temp){
    if(temp == NULL){
        return 0;
    }
    int lh  = Height(temp->left);
    int rh = Height (temp->right);
    return max(lh,rh)+1;
}

Dict* LeftLeftRotation(Dict *temp){
    Dict * t1 = temp->left;
    Dict * t2 = t1->right;
    t1->right = temp;
    temp->left = t2;
    return t1;
}

Dict* RightRightRotation(Dict *temp){
    Dict * t1 = temp->right;
    Dict * t2 = t1->left;
    t1->left = temp;
    temp->right = t2;
    return t1;
}
// left right and right left can be done using left left and right right

Dict* LeftRightRotation(Dict *temp){
    temp->left=RightRightRotation(temp->left);
    return LeftLeftRotation(temp);
}

Dict* RightLeftRotation(Dict *temp){
    temp->right = LeftLeftRotation(temp->right);
    return RightRightRotation(temp);
}

Dict*Insertion(Dict * &temp , Dict *t){
    if(temp ==NULL){
        temp = t;
        return temp;

    }
    else if(temp->id == t->id){
        temp->count++;
        // cout<<"key already present"<<endl;
        return temp;
    }
    else if(temp->id > t->id){
        // cout<<"check2"<<endl;
        temp->left=Insertion(temp->left,t);
    }
    else if(temp->id < t->id){
        temp->right  = Insertion(temp->right,t);
    }
    // cout<<"check3"<<endl;
    int lh = Height(temp->left);
    int rh = Height(temp->right);
    int hdiff = lh-rh;
        if(hdiff>1 && temp->left->id > t->id){
            return LeftLeftRotation(temp);
        }
        else if(hdiff<-1 && temp->right->id < t->id){
            return RightRightRotation(temp);
        }
        else if(hdiff>1 && temp->left->id < t->id){
            return LeftRightRotation(temp);
        }
        else if(hdiff<-1 && temp->right->id > t->id){
            return RightLeftRotation(temp);
        }
    return temp;
}
void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    for (char &c : sentence) {
       if (std::isupper(c)) {
           c = std::tolower(c);
       }
    }
    int si = sentence.size();
    string word = "";
    int i;
    for(i=0;i<si;i++){
        
        if(sentence[i] == ' ' || sentence[i] == '.' || sentence[i] == '-' || sentence[i] == ':'|| sentence[i] == '!' || sentence[i] == '"'|| sentence[i] == '\''|| sentence[i] == '('|| sentence[i] == ')'|| sentence[i] == '?'|| sentence[i] == '['|| sentence[i] == ']'|| sentence[i] == ';'|| sentence[i] == '@'|| sentence[i] == ','){
            if(word!=""){Dict * temp = new Dict(word);
            // cout<<word<<endl;
            root = Insertion(root , temp);}
            // cout<<temp->id<<endl;}
            // cout<<"insertion called "<<i<<endl;
            word = "";
        }
        else{
            word = word+sentence[i];
        }
    }
    if(i==si && word!=""){
        Dict * temp = new Dict(word);
        root = Insertion(root , temp); 
    }  
    return;
}

int Dict::get_word_count(string word){
    Dict * temp = get_root();
    while(temp != NULL){
        if(temp->id == word){
            return temp->count;
        }
        else if(temp->id > word){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    // Implement your function here  
    return -1;
}
void traversal(Dict * root,vector<string> &out){
    if(root ==NULL){
        return ;
    }
    traversal(root->left,out);
    // cout<<root->id<<endl;
    if(root->id !=" "){
    out.push_back(root->id+", "+to_string(root->count));}
    traversal(root->right , out);
}
void Dict::dump_dictionary(string filename){
    vector<string> commands;
    traversal(root, commands);
    ofstream out_file;
    out_file.open(filename);
    for (int i = 0 ; i<commands.size() ; i++){
        out_file<<commands[i]<<endl;
    }
    out_file.close();
    // Implement your function here  
    return;
}

Dict *Dict::get_root()
{
    return root;
}
Dict::~Dict(){
    // cout<<"destructor called"<<endl;
    delete left;
    delete right;
    // Implement your function here    
}


// tester code 
// don't forget to remove them

// #include <iostream>
// using namespace std;

// void display(Dict*root){
//     if(root ==NULL){
//         return;
//     }
//         display(root->left);
//         cout<<root->id<<" & "<<root->count<<" ";
//         display(root->right);
//         return;
    
// }
// int main(){
//     Dict * S  = new Dict();
//     S->insert_sentence(0,0,0,0,"3 drawers (woollen) 15 0 3 (cotton or merino) 6 0 3 Woollen vests 12 0 3 Cotton or merino vests 4 0 3 Woollen shirts without collars 16 0 6 Woollen shirts with collars 18 0 1 White shirt 2 0 1 Pair of braces 1 8 3 Standup collars 1 0 Mother of pearl studs 0 8  links 0 4 12Handkerchiefs 1 4 2 Sleeping suits (woollen) 15 0 1 Pair of gloves 2 0 1 Rug 10 0 6 Cotton or merino socks 3 0 3 Woollen socks 4 0");
//     S->dump_dictionary("output");
//     delete S;
//     // cout<<"delete done"<<endl;
//     // display(S->get_root());
//     // cout<<S->get_word_count("you")<<endl;
//     return 0;

// }