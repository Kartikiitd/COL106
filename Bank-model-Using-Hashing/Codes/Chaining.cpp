#include "Chaining.h"
#include <vector>
using namespace std;
#include <algorithm>
//use merge sort before submission

void Chaining::createAccount(std::string id, int count) {
    if(bankStorage2d.size()==0){
        size =0;
        for(int i=0; i< 100000 ; i++){
            vector<Account> alpha;
            bankStorage2d.push_back(alpha);
            }
        }
    int index = hash(id);
    Account a;
    a.id = id;
    a.balance = count;
    bankStorage2d[index].push_back(a);
    size++;
    // IMPLEMENT YOUR CODE HERE
}

std::vector<int> Chaining::getTopK(int k) {
    vector<int> sort_bal ;
    for(int i=0 ; i<100000 ;i++){
        int temp_size = bankStorage2d[i].size();
        if(temp_size !=0){
        for(int j=0; j<temp_size ; j++){
            sort_bal.push_back(bankStorage2d[i][j].balance);
        }}
    }
    sort(sort_bal.begin(),sort_bal.end());
    // for (int i =0;i<sort_bal.size();i++){
    //     for (int j=i;j<sort_bal.size();j++){
    //         if(sort_bal[j]<sort_bal[i]){
    //             int temp=sort_bal[j];
    //             sort_bal [j]=sort_bal[i];
    //             sort_bal[i]=temp;
    //         }
    //     }
    // }
    vector<int> output;
    for(int i =sort_bal.size()-1; i>=sort_bal.size()-k ;i--){
        output.push_back(sort_bal[i]);
    }
    // IMPLEMENT YOUR CODE HERE
    return output; // Placeholder return value
}

int Chaining::getBalance(std::string id) {
    int index = hash(id);
    if(doesExist(id)==false){
        return -1;
    }
    int temp_size = bankStorage2d[index].size();
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

void Chaining::addTransaction(std::string id, int count) {
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

bool Chaining::doesExist(std::string id) {
    if(databaseSize() == 0){
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
    // IMPLEMENT YOUR CODE 
    return false; // Placeholder return value
}

bool Chaining::deleteAccount(std::string id) {
    if(doesExist(id)==false){
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
    // IMPLEMENT YOUR CODE HERE
    return false; // Placeholder return value
}
int Chaining::databaseSize() {
    return size;
    // IMPLEMENT YOUR CODE HERE
    return 0; // Placeholder return value
}

int Chaining::hash(std::string id) {
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
/*
int main(){
Chaining *c = new Chaining();
c->createAccount("CDAD7786825_7990768648",648);
c->createAccount("DCDA7547234_9919615552" ,552);
c->createAccount("AACB1850545_7974534788" , 788);
cout<<c->doesExist("CDBF1234567_1234567890")<<endl;
c->addTransaction("CDBF1234567_1234567890" , 123);
cout<<c->doesExist("CDBF1234567_1234567890")<<endl;
// cout<<c->doesExist("AACB1850545_7974534789")<<endl;
// cout<<c->doesExist("AACB1850545_7974534789")<<endl;
cout<<c->databaseSize()<<endl;
// cout<<c->hash("CDBD5250777_1124276711")<<endl;
// cout<<c->hash("ABCB8377155_0656808575")<<endl;
c->createAccount("CDBD5250777_1124276711" , 711);
c->createAccount("ABCB8377155_0656808575" , 575);
// cout<<1;
std::vector<int> ans=c->getTopK(1); 
for(int i=0;i<ans.size();i++){
    cout<<ans[i]<<" ";
}cout<<endl;
c->createAccount("CDDC3792028_3313680038" , 38);
c->createAccount("CBBA9574444_7470182321", 321);
c->createAccount("DBCC4334636_8057544188", 188);
std::vector<int> ans2=c->getTopK(3);
for(int i=0;i<ans2.size();i++){
    cout<<ans2[i]<<" ";
}cout<<endl;
c->createAccount("BABD5741078_5109455304", 304);
c->createAccount("BCBA7529510_0817878868", 868);
cout<<c->databaseSize()<<endl;
std::vector<int> ans3=c->getTopK(1); 
for(int i=0;i<ans3.size();i++){
    cout<<ans3[i]<<" ";
}cout<<endl;
c->addTransaction("BCBA7529510_0817878868", -860); 
cout<<c->getBalance("BCBA7529510_0817878868")<<endl;
std::vector<int> ans4=c->getTopK(1); 
for(int i=0;i<ans4.size();i++){
    cout<<ans4[i]<<" ";
}cout<<endl;
c->addTransaction("DCDA7547234_9919615552", 592);
std::vector<int> ans5=c->getTopK(5); 
for(int i=0;i<ans5.size();i++){
    cout<<ans5[i]<<" ";
}cout<<endl;
// cout<<c->hash("DCDA7547234_9919615552")<<endl;
c->deleteAccount("DCDA7547234_9919615552");
// c->createAccount("DCDA7547234_9919615552" ,552);
cout<<c->getBalance("DCDA7547234_9919615552")<<endl;
// cout<<c->hash("DCDA7547234_9919615552")<<endl;

std::vector<int> ans6=c->getTopK(4); 
for(int i=0;i<ans6.size();i++){
    cout<<ans6[i]<<" ";
}cout<<endl;
cout<<c->databaseSize()<<endl;
    return 0;
}


*/