# include <iostream>
#include <vector>
using namespace std;
class SET{
    public:
    vector <int> v;
    SET(){
        v={};
    }
    

    void Insert(int data){
        if(v.empty()){
            v.push_back(data);
            return;
        }
        else{
            for(int i=0; i<v.size(); i++){
                if (v[i]==data){
                    return;
                }}
            
            if (v[0] > data) {
            v.insert(v.begin(), data); 
            return;
            }
            int it=0;
            for(int i=0; i<v.size();i++){
                
                if(v[i]>data){
                    it=i;
                    break;
                }
                if(i==v.size()-1){
                    it=v.size();
                    break;
                }
            }
            v.insert(v.begin()+it,data);
            return;
                  
        
    }
    }
    void Union(SET p){
        vector <int> second = p.v;
        if (second.empty()){
            return;
        }
        if(v.empty()){
            v=second;
            return;
        }
        else{
            for (int i=0 ; i<second.size() ; i++){
                Insert(second[i]);
            }
            return;
        }

    }
    void SymmetricDifference(SET p){
        vector <int> second = p.v;
        if (second.empty()){
            return;
        }
        if(v.empty()){
            v=second;
            return;
        }
        
        else{
            
            vector <int> newarr={};
            SET q;
            vector <int> third = q.v;
            third = {};
            for (int i=0 ; i<v.size() ; i++){
                if( newbelong(v[i],second )){
                    third.push_back(v[i]);
                }
            }
            for (int i=0 ; i<second.size() ; i++){
                Insert(second[i]);
            }
            for (int i=0 ; i<v.size() ; i++){
                if(! newbelong(v[i],third )){
                    newarr.push_back(v[i]);
                }
            }
            v = newarr;
            return;
        }

    }

    void Intersection(SET p){
        vector <int> second = p.v;
        if (second.empty()){
            v={};
            return;
        }
        if(v.empty()){
            v={};
            return;
        }
        
        else{
            vector <int> newarr={};
            for (int i=0 ; i<second.size() ; i++){
                if(newbelong(second[i],v)){
                    newarr.push_back(second[i]);
                }
            }
            v = newarr;
            return;
        }

    }
    void Difference(SET p){
        vector <int> second = p.v;
        if (second.empty()){
            return;
        }
        if(v.empty()){
            return;
        }
        
        else{
            vector <int> newarr={};
            for (int i=0 ; i<v.size() ; i++){
                if(! newbelong(v[i],second)){
                    newarr.push_back(v[i]);
                }
            }
            v = newarr;
            return;
        }

    }


    bool newbelong(int data,vector <int> che){
        for(int i=0 ; i<che.size() ; i++){
            if (data==che[i]){
                return true;
            }
        }
        return false;
    }
    void Delete(int data){
        if (v.empty()){
            cout<<v.size()<<endl;
        }
        else{
            for(int i = 0; i<v.size() ; i++){
                if(v[i]==data){
                    v.erase(v.begin()+i);
                    cout<<v.size()<<endl;
                    return ;
                }}
                cout<<v.size()<<endl;
                return ;
        }
    }

    void Belongs_to(int data){
        if(v.empty()){
            cout<<0<<endl;
        }
        else{
            for(int i = 0; i<v.size() ; i++){
                if(v[i]==data){
                    cout<<1<<endl;
                    return ;
                }}
            cout<<0<<endl;
            return;

        }
    }

    void Size(){
        cout<<v.size()<<endl;
    }

    void Print(){
        if (v.empty()){
            cout<<endl;
            return;
        }
        else{
        for (int i = 0; i < v.size(); i++) {
        if(i  != v.size()-1){
        cout << v[i] << ",";}
        else{
            cout<<v[i];
        }
        
    }}
    cout << endl;

    }
};

vector <SET> l;

int main(){
    
    int code;
    while(cin>>code){    
        int name,data;
        cin>>name;
        switch (code)
       
        {
        case 1:
            cin>>data;
            if(name<l.size()){
                l[name].Insert(data);
                l[name].Size();
            }
            else{
            SET vx;
           
            vx.Insert(data);
            vx.Size();
            l.push_back(vx);

            }
            
            break;
        case 2:
            cin>>data;
            if(name<l.size()){
                l[name].Delete(data);
            }
            else{
            cout<<-1<<endl;
            }
            break;
        case 3:
            cin>>data;
            if(name<l.size()){
                l[name].Belongs_to(data);
            }
            else{
            cout<<-1<<endl;
            }
            break;

        case 4:
            cin>>data;
            if(name<l.size() && data <l.size()){
                
                l[name].Union(l[data]);
                l[name].Size();
            }
            if(name>=l.size() && data >=l.size()  && name !=data){
                SET new1;
                SET new2;
                l.push_back(new1);
                l.push_back(new2);
                cout<<0<<endl;


            }
            if(name>=l.size()){
                SET new3;
                l.push_back(new3);
                // l[data].Size();
                l[name].Union(l[data]);
                l[name].Size();
            }
            if(data>=l.size()){
                SET new4;
                l.push_back(new4);
                // l[name].Size();
                l[name].Union(l[data]);
                l[name].Size();
            }
            break;

        case 5:
            cin>>data;
            if(name<l.size() && data <l.size()){
                
                l[name].Intersection(l[data]);
                l[name].Size();
            }
            if(name>=l.size() && data >=l.size()  && name !=data){
                SET new1;
                SET new2;
                l.push_back(new1);
                l.push_back(new2);
                cout<<0<<endl;
            }
            if(name>=l.size()){
                SET new3;
                l.push_back(new3);
                // cout<<0<<endl;
                l[name].Intersection(l[data]);
                l[name].Size();
            }
            if(data>=l.size()){
                SET new4;
                l.push_back(new4);
                l[name]={};
                // l[name].Size();
                l[name].Intersection(l[data]);
                l[name].Size();
            }
            break;    

        case 6:
            if(name<l.size()){
                l[name].Size();
            }
            else{
            cout<<0<<endl;
            SET vx;
            l.push_back(vx);
            }
            break;

        case 7:
            cin>>data;
            if(name<l.size() && data <l.size()){
                
                l[name].Difference(l[data]);
                l[name].Size();
            }
            if(name>=l.size() && data >=l.size()  && name !=data){
                SET new1;
                SET new2;
                l.push_back(new1);
                l.push_back(new2);
                cout<<0<<endl;
            }
            if(name>=l.size()){
                SET new3;
                l.push_back(new3);
                // cout<<0<<endl;
                l[name].Difference(l[data]);
                l[name].Size();
            }
            if(data>=l.size()){
                SET new4;
                l.push_back(new4);
                // l[name].Size();
                l[name].Difference(l[data]);
                l[name].Size();
            }
            break;

        case 8:
            cin>>data;
            if(name<l.size() && data <l.size()){
                
                l[name].SymmetricDifference(l[data]);
                l[name].Size();
            }
            if(name>=l.size() && data >=l.size()  && name !=data){
                SET new1;
                SET new2;
                l.push_back(new1);
                l.push_back(new2);
                cout<<0<<endl;
            }
            if(name>=l.size()){
                SET new3;
                l.push_back(new3);
                // cout<<0<<endl;
                l[name].SymmetricDifference(l[data]);
                l[name].Size();
            }
            if(data>=l.size()){
                SET new4;
                l.push_back(new4);
                // l[name].Size();
                l[name].SymmetricDifference(l[data]);
                l[name].Size();
            }
            break;
        case 9:
            if(name<l.size()){
                l[name].Print();
            }
            else{
            cout<<endl;
            }
            break;
        
        }
    }
    return 0;
}


