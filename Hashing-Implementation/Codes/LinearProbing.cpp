#include "LinearProbing.h"
#include <vector>
using namespace std;
void LinearProbing::createAccount(std::string id, int count) {
    if(bankStorage1d.size()==0){
        size = 0;
        for(int i=0; i< 101000 ; i++){
            Account alpha;
            alpha.id = "0";
            bankStorage1d.push_back(alpha);
            }
    }
    int index = hash(id);
    if(bankStorage1d[index].id =="0"){
        bankStorage1d[index].id = id;
        bankStorage1d[index].balance = count;
        size++;
        return;
    }
    int temp_index = index;
    while(bankStorage1d[temp_index].id !="0"){
        temp_index = (temp_index + 1)%101000;
    }
    bankStorage1d[temp_index].id = id;
    bankStorage1d[temp_index].balance = count;
    size++;
    return ; 
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> LinearProbing::getTopK(int k) {
    vector<int> sort_bal;
    for(int i=0 ; i<101000 ; i++){
        if(bankStorage1d[i].id != "0"){
            sort_bal.push_back(bankStorage1d[i].balance);
        }
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

int LinearProbing::getBalance(std::string id) {
    int index = hash(id);
    if(doesExist(id) == false){
        return -1;
    }
    if(bankStorage1d[index].id == id){
        return bankStorage1d[index].balance;
    }
    int temp_index = index ;
    while (bankStorage1d[temp_index].id != id){
        temp_index = (temp_index +1)%101000 ; 
    }
    if(bankStorage1d[temp_index].id == id){
        return bankStorage1d[temp_index].balance;
    }
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

void LinearProbing::addTransaction(std::string id, int count) {
    int index = hash(id) ;
    int temp_index = index;
    if(doesExist(id) == false){
        createAccount(id , count);
        return ;
    }
    if(doesExist(id) == true){
        for (int i=0 ; i<101000 ; i++){
        if(bankStorage1d[temp_index].id == id){
            bankStorage1d[temp_index].balance += count ;
            return ;
        }
        temp_index = (temp_index + 1)%101000;
    }
    }
    // IMPLEMENT YOUR CODE HERE
}

bool LinearProbing::doesExist(std::string id) {
    int index = hash(id) ;
    int temp_index = index;
    for (int i=0 ; i<101000 ; i++){
        if(bankStorage1d[temp_index].id == id){
            return true;
        }
        temp_index = (temp_index + 1)%101000;
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}

bool LinearProbing::deleteAccount(std::string id) {
    int index = hash(id) ;
    int temp_index = index;
    if(doesExist(id) == false){
        return false;
    }
    if(doesExist(id) == true){
        for (int i=0 ; i<101000 ; i++){
        if(bankStorage1d[temp_index].id == id){
            bankStorage1d[temp_index].id = "0" ;
            size--;
            return true;
        }
        temp_index = (temp_index + 1)%101000;
    }
    }
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int LinearProbing::databaseSize() {
    return size;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

int LinearProbing::hash(std::string id) {
    int hash_index = 0;
    int curr_coeff = 1;
    for(int i=id.length()-1;i>=16;i--){
        hash_index += id[i] * curr_coeff;
        hash_index = hash_index % 101000;
        curr_coeff *=11;
        curr_coeff = curr_coeff % 101000;
    }
    return hash_index % 101000;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

