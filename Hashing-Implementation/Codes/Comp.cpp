#include "Comp.h"
#include <vector>
using namespace std;

//before submission check for transaction negative balance 
// also check for double return statements 

void Comp::createAccount(std::string id, int count) {
    // bool g = existence; 
    if(bankStorage2d.size()==0){
        size =0;
        for(int i=0; i< 100000 ; i++){
            vector<Account> alpha;
            bankStorage2d.push_back(alpha);
            }
        }
    // existence = true;}
    int index = hash(id);
    Account a;
    a.id = id;
    a.balance = count;
    bankStorage2d[index].push_back(a);
    size++;
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Comp::getTopK(int k) {
    vector<int> sort_bal ;
    for(int i=0 ; i<100000 ;i++){
        int temp_size = bankStorage2d[i].size();
        if(temp_size !=0){
        for(int j=0; j<temp_size ; j++){
            // cout<<"go"<<" ";
            sort_bal.push_back(bankStorage2d[i][j].balance);
        }}
    }
    for (int i =0;i<sort_bal.size();i++){
        for (int j=i;j<sort_bal.size();j++){
            if(sort_bal[j]<sort_bal[i]){
                int temp=sort_bal[j];
                sort_bal [j]=sort_bal[i];
                sort_bal[i]=temp;
            }
        }
    }
    vector <int> output;
    for(int i =sort_bal.size()-1; i>=sort_bal.size()-k ;i--){
        output.push_back(sort_bal[i]);
    }
    // IMPLEMENT YOUR CODE HERE
    return output; // Placeholder return value
}

int Comp::getBalance(std::string id) {
    int index = hash(id);
    if(databaseSize() ==0){
        return -1;
    }
    int temp_size = bankStorage2d[index].size();
    if(!doesExist(id)){
        return -1;
    }
    for(int i=0 ; i<temp_size ; i++){
        Account temp_acc = bankStorage2d[index][i];
        if (temp_acc.id == id){
            return temp_acc.balance;
        }
    }
    return -1;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

void Comp::addTransaction(std::string id, int count) {

    int index = hash(id);
    
    if(doesExist(id)==true){
    int temp_size = bankStorage2d[index].size();
    for(int i=0 ; i<temp_size ; i++){
        Account temp_acc = bankStorage2d[index][i];
        if(temp_acc.id == id ){
            bankStorage2d[index][i].balance += count ;
            return;
        }
    }
    }
    if(doesExist (id) == false){
        createAccount(id , count);
    }
    // IMPLEMENT YOUR CODE HERE
}

bool Comp::doesExist(std::string id) {
    if(databaseSize() ==0){
        return false;
    }
    int index = hash(id);
    int temp_size = bankStorage2d[index].size();
    for(int i=0 ; i<temp_size ; i++){
        Account temp_acc = bankStorage2d[index][i];
        if(temp_acc.id == id ){
            return true;
        }
    }
    // return false;
    // IMPLEMENT YOUR CODE 
    return false; // Placeholder return value
}

bool Comp::deleteAccount(std::string id) {
    if(databaseSize() ==0){
        return false;
    }
    int index = hash(id);
    int temp_size = bankStorage2d[index].size();
    
    
    for(int i=0 ; i<temp_size ; i++){
        Account temp_acc = bankStorage2d[index][i];
        if(temp_acc.id == id ){
            bankStorage2d[index].erase(bankStorage2d[index].begin()+i);//make the id to zero
            size--;
            return true;
        }
    }
    // return false;
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Comp::databaseSize() {
    return size;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

int Comp::hash(std::string id) {
    long long  hash_index = 0;
    long long  curr_coeff = 1;
    long long sz = 100000;
    long long ee = 5;
    for(int i=id.length()-1;i>=14;i--){
        long long k = id[i];
        hash_index += k * curr_coeff;
        hash_index = hash_index % sz;
        curr_coeff *=ee;
        curr_coeff = curr_coeff % sz;
    }
    return hash_index % sz;
    // IMPLEMENT YOUR CODE HERE

    return 0; // Placeholder return value
}