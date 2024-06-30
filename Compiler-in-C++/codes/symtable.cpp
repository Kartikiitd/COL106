/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

// #include <iostream>
// using namespace std;
// don't forget to erase includes
// don't forget to erase includes
// don't forget to erase includes
// don't forget to erase includes


SymbolTable::SymbolTable(){
    size = 0 ;
    root = NULL;
}

int Height(SymNode * temp){
    if(temp == NULL){
        return 0;
    }
    int lh  = Height(temp->left);
    int rh = Height (temp->right);
    return max(lh,rh)+1;
}
void Update_tree(SymNode * temp){
    if(temp->left==NULL && temp->right==NULL){
        temp->height = 1;
        return ; 
    }
    if(temp->left!=NULL){
        Update_tree(temp->left);
    }
    
    // cout<<"Ut3"<<endl;
    if(temp->right!=NULL){
         Update_tree(temp->right);
    }
   
    
    temp->height = Height(temp);
    // cout<<"update tree"<<endl;
    
}
SymNode* LeftLeftRotation(SymNode *temp){
    SymNode * t1 = temp->left;
    SymNode * t2 = t1->right;
    t1->right = temp;
    temp->left = t2;
    // cout<<"LLR"<<endl;
    return t1;
}

SymNode* RightRightRotation(SymNode *temp){
    // cout<<"RRR called"<<endl;
    SymNode * t1 = temp->right;
    // cout<<"hi1"<<endl;
    SymNode * t2 = t1->left;
    // cout<<"hi2"<<endl;
    t1->left = temp;
    temp->right = t2;
    // cout<<"RRR executed"<<endl;
    return t1;
}
// left right and right left can be done using left left and right right

SymNode* LeftRightRotation(SymNode *temp){
    temp->left=RightRightRotation(temp->left);
    // cout<<"LRR"<<endl;
    return LeftLeftRotation(temp);
}

SymNode* RightLeftRotation(SymNode *temp){
    temp->right = LeftLeftRotation(temp->right);
    // cout<<"RLR"<<endl;
    return RightRightRotation(temp);
}

SymNode*Insertion(SymNode * temp , SymNode *t){
    if(temp ==NULL){
        temp = t;
        // cout<<"check1"<<endl;
        return temp;

    }
    else if(temp->key > t->key){//means temp is greater than the k ; so left
        // cout<<"check2"<<endl;
        temp->left=Insertion(temp->left,t);
    }
    else if(temp->key < t->key){
        temp->right  = Insertion(temp->right,t);
    }
    // cout<<"check3"<<endl;
    int lh = Height(temp->left);
    int rh = Height(temp->right);
    int hdiff = lh-rh;
        if(hdiff>1 && temp->left->key > t->key){
            //case for left left
            // cout<<"check1"<<endl;
            return LeftLeftRotation(temp);
        }
        else if(hdiff<-1 && temp->right->key < t->key){
            //case for right right
            // cout<<"check3"<<endl;
            return RightRightRotation(temp);
        }
        else if(hdiff>1 && temp->left->key < t->key){
            //case for left right
            // cout<<"check2"<<endl;
            return LeftRightRotation(temp);
        }
        else if(hdiff<-1 && temp->right->key > t->key){
            //case for right left
            // cout<<"check4"<<endl;
            return RightLeftRotation(temp);
        }
    return temp;
    //keep in mind that the height for NULl is 0 while for a single node is 1;
    // during this insertion update height of each node ,size, address can be done later
}
void SymbolTable::insert(string k){
    SymNode * t = new SymNode(k);
    SymNode * tem = Insertion(root,t);
    root = tem;
    size++;
    Update_tree(root);
    return ;
}
bool searchkey(SymNode * temp ,string k){
    bool c = false;
    if(temp==NULL){
        c = false;
        return c;
    }
    else if (temp->key == k){
        c = true;
        return c;
    }
    else if(k > temp->key){
        c = searchkey(temp->right,k);
    }
    else {
        c = searchkey(temp->left,k);
    }
    return c;
}
SymNode * Deletenode(SymNode * temp , string k){
    if(temp ==NULL){
        return temp;
    }
    else if(k>temp->key){//k is in rhs of temp
        // cout<<"case 1 found"<<endl;
        temp->right = Deletenode(temp->right,k);
    
    }
    else if(k<temp->key){//k is in lhs of temp
        // cout<<"case 2 found"<<endl;
        temp->left = Deletenode(temp->left,k);
    }
    else{//k is same as the temp->key;
        // cout<<"case 3 found"<<endl;
        if(temp->left ==NULL){
            SymNode * t1 = temp->right;
             temp->left=NULL;
            temp->right=NULL;
            delete temp;
            return t1;
        }
        else if(temp->right ==NULL){
            SymNode * t2 = temp->left;
            temp->left=NULL;
            temp->right=NULL;
            delete temp;
            return t2;
        }
        else{
            // cout<<"key found and deletion called"<<endl;
            SymNode * t = temp->left;
            while(t->right != NULL){
                t = t->right;// inorder predecessor is found here;
            }
            string tk = t->key;
            temp->key = tk;
            temp->left = Deletenode(temp->left , tk);
        }
        
    }
    // now do the balancing thing 
    int lh = Height(temp->left);
    int rh = Height(temp->right);
    int hdiff = (lh-rh);
        if( hdiff>1 && Height(temp->left->left)-Height(temp->left->right)>=0){
            //case for left left
            // cout<<"check1"<<endl;
            return LeftLeftRotation(temp);
        }
        else if(hdiff<-1 && Height(temp->right->left)-Height(temp->right->right) <= 0){
            //case for right right
            // cout<<"check3"<<endl;
            return RightRightRotation(temp);
        }
        else if(hdiff>1 && Height(temp->left->left)-Height(temp->left->right)<0){
            //case for left right
            // cout<<"check2"<<endl;
            return LeftRightRotation(temp);
        }
        else if(hdiff<-1 && Height(temp->right->left)-Height(temp->right->right) > 0 ){
            //case for right left
            // cout<<"check4"<<endl;
            return RightLeftRotation(temp);
        
    }
    return temp;
}

void SymbolTable::remove(string k){
    if(root->key == k && size == 1){
        root = NULL;
        size--;
        return;
    }
    if(searchkey(root,k)){
    SymNode * t = Deletenode(root,k);
    root = t;
    size--;
    Update_tree(root);}
    return;
}
//verify for search and assign address others are correct 
int SymbolTable::search(string k){
    if(root ==NULL){
        return -2;
    }
    SymNode * temp = root;
    while(temp != NULL && temp->key != k){
        
        if(temp->key > k){
            temp = temp -> left;
        }
        else{
            temp = temp->right;
        }
    }
    if(temp!=NULL && temp->key == k){
            return temp->address;
        }
    return -2;
}

void SymbolTable::assign_address(string k,int idx){
    if (root ==NULL){
        return ;
    }
    SymNode * temp = root;
    while(temp !=NULL && temp->key != k){
        if(temp->key > k){
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    if(temp!=NULL && temp->key == k ){//cam modify here for assigning index if already done
            temp->address = idx;
            return;
        }
    return;
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}
 // don't forget to remove this function
// void inorder(SymNode* root){
//     if (root == NULL){
//         return ;
//         }
//     else{
//         inorder(root->left);
//         cout<<root->key<<"("<<root->height<<")"<<" ";
//         inorder(root->right);
//     }
// }
/*
int main(){
    SymbolTable* S = new SymbolTable();
    S->insert("ab");
    // SymNode *t = S->get_root();
    // cout<<"hello1"<<endl;
    // cout<<t->key<<endl;
    S->insert("a");
    // cout<<"hello2"<<endl;
    S->insert("c");
    // cout<<"hello3"<<endl;
    S->insert("g");
    // cout<<"hello4"<<endl;
    S->insert("e");
    // cout<<"hello5"<<endl;
    // S->insert("f");
    // cout<<"hello6"<<endl;
    cout<<S->get_root()->key<<" "<<S->get_size()<<endl;
    inorder(S->get_root());
    cout<<endl;
    // S->assign_address("a",1);
    // S->assign_address("b",2);
    // S->assign_address("c",3);
    // S->assign_address("d",4);
    // cout<<S->search("d")<<endl;
    // cout<<S->search("c")<<endl;
    // cout<<S->search("g")<<endl;
    // cout<<S->search("d")<<endl;
    // cout<<S->search("c")<<endl;
    // S->remove("d");
    // cout<<S->get_root()->key<<" "<<S->get_size()<<endl;
    // inorder(S->get_root());
    // cout<<endl;
    // S->remove("c");
    // cout<<S->get_root()->key<<" "<<S->get_size()<<endl;
    // inorder(S->get_root());
    // cout<<endl;
    // S->remove("d");
    // S->remove("a");
    // cout<<S->get_root()->key<<" "<<S->get_size()<<endl;
    // inorder(S->get_root());
    // cout<<endl; 
    return 0;
}
*/
/*
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

#include <time.h>
#include <algorithm>  
using namespace std;

void print_dfs(SymNode * root){
    
    vector<SymNode *> q;
    q.push_back(root);
    
    vector<vector<string> > total_display;
    vector<string> temop;
    temop.push_back(root->key);
    total_display.push_back(temop);
    bool k=true;
    while(k){
        vector<SymNode *> temp;
        vector<string> display;
        for(int i=0;i<q.size();i++){
            if(q[i]==NULL){
                temp.push_back(NULL);
                temp.push_back(NULL);
                display.push_back("#");
            }
            else{
                if(q[i]->left==NULL){
                    temp.push_back(q[i]->left);
                    display.push_back("#");
                }
                else{
                    temp.push_back(q[i]->left);
                    display.push_back(q[i]->left->key);

                }
                if(q[i]->right==NULL){
                    temp.push_back(NULL);
                    display.push_back("#");

                }
                else{
                    temp.push_back(q[i]->right);
                    display.push_back(q[i]->right->key);

                }


            }
        }
        q.clear();
        k=false;
        for(int i=0;i<temp.size();i++){
            if(temp[i]!=NULL){
                k=true;
            }
            q.push_back(temp[i]);
        }
        if(!k){
            break;
        }
        
        total_display.push_back(display);
        
    }
    int side=1;
    for(int i=0;i<total_display.size();i++){
        side=side*2;
    }
    side=side*2;
    

    for(int i=0;i<total_display.size();i++){
        for(int j=0;j<side/2+1;j++){
            cout<<" ";
        }
        
        for(int j=0;j<total_display[i].size();j++){
            cout<<total_display[i][j];
            for(int k=0;k<side;k++){
                cout<<" ";
            }
        }
        side/=2;
        cout<<endl;
    }

    return;


}
int depth (SymNode *root) {
    if (root == NULL) return 0;
    return max (depth(root -> left), depth (root -> right)) + 1;
}

bool isBalanced (SymNode *root) {
    if (root == NULL) return true;

    int left=depth(root->left);
    int right=depth(root->right);

    return abs(left - right) <= 1 && isBalanced(root->left) && isBalanced(root->right);
}
bool isValidBST(SymNode * root, SymNode * minNode,SymNode * maxNode) {
    if(!root) return true;
    if(minNode && root->key <= minNode->key || maxNode && root->key >= maxNode->key)
        return false;
    return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
}
int main(){
    bool multiple_test=true;
    if(multiple_test){
        int test_casses=500;
    
    cout<<"start"<<endl;
    srand(time(0));
    for(int test=0;test<test_casses;test++){
        if(test%(max(1,test_casses/100))==0){
            cout<<"-"<<flush;
        }
        SymbolTable * s=new SymbolTable();
        
        
        map<string,int> m;
        int n=1000;
        //int a[n]={6,9,1,4,2,0,7,5,8,3};
        vector<string> nodes;
        for(int i=0;i<n;i++){
            //string node=to_string(rand());
            //string node=to_string(a[i]);
            string node="";
            //cin>>node;
            //if(node=="!"){
            //    break;
            //}
            node+=to_string(rand());
        // n++;
            
            

            if(m.find(node)!=m.end()){
                node+=to_string(rand());
                m[node]=1;
            }
            else{
                m[node]=1;
            }
            nodes.push_back(node);
            //nodes.push_back(node);
            s->insert(node);
            // if(%(n/10)==0){
            //     cout<<"-"<<flush;
            // }
            if(s->get_size()!=i+1){
                cout<<"size not correct "<<s->get_size()<<endl;
            }
            //cout<<"done "<<i<<endl;

            // cout<<"root is "<<s->get_root()->key<<endl;
            // print_dfs(s->get_root());
            //cout<<"------"<<endl;
            
        }
        //cout<<endl;
        // print_dfs(s->get_root());
        // cout<<"insertion complete"<<endl;


        if(isBalanced(s->get_root()) && isValidBST(s->get_root(), NULL, NULL) ){
        //    cout<<"ITS AN AVL TREE :)"<<endl;

        }
        else{
            
            cout<<endl;
            cout<<"NOOOO its not an avl tree :("<<endl;
        
        }
        //return 0;
        bool all_found=true;
        for(int i=0;i<n;i++){
            if(s->search(nodes[i])==-2){
                cout<<" WRONG AVL :( cannnot find "<<nodes[i]<<endl;
                //break;
                all_found=false;
            }
            
        }
        if(all_found){
            // cout<<"ALL nodes are present"<<endl;
        }
        
        

        // for(int jj=0;jj<nodes.size();jj++){
        //     cout<<nodes[jj]<<" "<<flush;
        // }
        // cout<<endl;
        // print_dfs(s->get_root());
        for(int i=0;i<nodes.size();i++){

            // cout<<"deleting "<<nodes[i]<< " === > "<<endl;
            s->remove(nodes[i]);
            // cout<<"delted"<<nodes[i]<<endl;
            
            if(s->get_size()==0){
                if(s->get_root()==NULL){
                    //cout<<"deletion COMPLETE :)"<<endl;
                    break;
                }
                else{
                    cout<<"root not set properly :("<<endl;
                    break;
                }
                
            }
            //print_dfs(s->get_root());
            if(!isBalanced(s->get_root()) || !isValidBST(s->get_root(), NULL, NULL)){
                
                cout<<"NOOO failed at "<<i<<" index/iteration"<<endl;
                break;
            }
            //cout<<"here"<<endl;
            if(s->get_size()!=n-i-1){
                //print_dfs(s->get_root());
                cout<<"WRONG size"<<endl;
                break;
            }

        }
        
        nodes.clear();
        //int a[n]={6,9,1,4,2,0,7,5,8,3};
        
        for(int i=0;i<n;i++){
            //string node=to_string(rand());
            //string node=to_string(a[i]);
            string node="";
            //cin>>node;
            //if(node=="!"){
            //    break;
            //}
            node+=to_string(rand());
        // n++;
            
            

            if(m.find(node)!=m.end()){
                node+=to_string(rand());
                m[node]=1;
            }
            else{
                m[node]=1;
            }
            nodes.push_back(node);
            //nodes.push_back(node);
            s->insert(node);
            // if(%(n/10)==0){
            //     cout<<"-"<<flush;
            // }
            if(s->get_size()!=i+1){
                cout<<"size not correct "<<s->get_size()<<endl;
            }
            //cout<<"done "<<i<<endl;

            // cout<<"root is "<<s->get_root()->key<<endl;
            // print_dfs(s->get_root());
            //cout<<"------"<<endl;
            
        }
        //cout<<endl;
        // print_dfs(s->get_root());
        // cout<<"insertion complete"<<endl;


        if(isBalanced(s->get_root()) && isValidBST(s->get_root(), NULL, NULL) ){
        //    cout<<"ITS AN AVL TREE :)"<<endl;

        }
        else{
            
            cout<<endl;
            cout<<"NOOOO its not an avl tree :("<<endl;
        
        }
        //return 0;
        all_found=true;
        for(int i=0;i<n;i++){
            if(s->search(nodes[i])==-2){
                cout<<" WRONG AVL :( cannnot find "<<nodes[i]<<endl;
                //break;
                all_found=false;
            }
            
        }
        if(all_found){
            // cout<<"ALL nodes are present"<<endl;
        }
        
        

        // for(int jj=0;jj<nodes.size();jj++){
        //     cout<<nodes[jj]<<" "<<flush;
        // }
        // cout<<endl;
        // print_dfs(s->get_root());
        for(int i=0;i<nodes.size();i++){

            // cout<<"deleting "<<nodes[i]<< " === > "<<endl;
            s->remove(nodes[i]);
            // cout<<"delted"<<nodes[i]<<endl;
            
            if(s->get_size()==0){
                if(s->get_root()==NULL){
                    //cout<<"deletion COMPLETE :)"<<endl;
                    break;
                }
                else{
                    cout<<"root not set properly :("<<endl;
                    break;
                }
                
            }
            //print_dfs(s->get_root());
            if(!isBalanced(s->get_root()) || !isValidBST(s->get_root(), NULL, NULL)){
                
                cout<<"NOOO failed at "<<i<<" index/iteration"<<endl;
                break;
            }
            //cout<<"here"<<endl;
            if(s->get_size()!=n-i-1){
                //print_dfs(s->get_root());
                cout<<"WRONG size"<<endl;
                break;
            }

        }
        //cout<<"passed"<<endl;

        
        
        delete s;
        

    }
    }
    else{
        
        SymbolTable * s=new SymbolTable();
        
        
        s->insert("a");
        //print_dfs(s->get_root());
        s->insert("c");
        //print_dfs(s->get_root());
        s->insert("d");
        //print_dfs(s->get_root());
        
        //print_dfs(s->get_root());
        
        s->remove("b");
        //print_dfs(s->get_root());
        s->remove("c");
        //print_dfs(s->get_root());
        s->remove("e");
        //print_dfs(s->get_root());
        s->remove("f");
        print_dfs(s->get_root());
        if(s->get_root()->par==NULL){
            cout<<"YAY"<<endl;
        }
        cout<<endl;
        s->insert("f");
        print_dfs(s->get_root());
        cout<<endl;
        cout<<s->get_size()<<endl;

        cout<<endl;
        s->insert("u");
        cout<<s->get_size()<<endl;
        print_dfs(s->get_root());




        
        
        delete s;
        cout<<"UWU"<<endl;


    }

    cout<<"UWU"<<endl;
    return 0;
}


//end */
