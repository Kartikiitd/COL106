// Do NOT add any other includes
#include "search.h"

void insert(Node* &root, Node* n){
    if(root==NULL){
        root=n;
        return;
    }
    n->left=root;
    n->right=root->right;
    root->right=n;
}

void getarray(string &pattern, int len, int* p){
	for (char &c : pattern) {
       if (std::isupper(c)) {
           c = std::tolower(c);
       }
    }
    p[0] = 0;
    int l = 0;
	int i = 1;
	while(i<len){
		// if(std::isupper(pattern[i])){
        //     pattern[i] = std::tolower(pattern[i]);
        // }
        if (pattern[i]==pattern[l]){
			l++;
			p[i] = l;
			i++;
	}
		else{
			if (l!=0){
				l=p[l-1];
			}
			else{
				p[i] = 0;
				i++;}
	}}
}

void searchpat(Node* &root, string pat, string txt, int p, vector<int> &a, vector<int> &b, vector<int> &c, vector<int> &d){
	
    int l1= pat.size();
	int l2= txt.size();
    int lps[l1];

	getarray(pat,l1,lps);

	int i=0;
	int j=0;
	while ((l2 - i)>=(l1 - j)){
		if(std::isupper(txt[i])){
            txt[i] = std::tolower(txt[i]);
        }
        if(pat[j]==txt[i]) {
			i++;
			j++;
		}
		if (j==l1){
            Node* n=new Node(a[p], b[p], c[p], d[p], i-j);
            insert(root,n);
			j = lps[j-1];
		}
		else if(i < l2 && pat[j] != txt[i]){
			if(j!= 0){
				j=lps[j-1];}
			else{
				i++;
            }
	}}
}

SearchEngine::SearchEngine(){
}

SearchEngine::~SearchEngine(){
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){

    v.push_back(sentence);
    a.push_back(book_code);
    b.push_back(page);
    c.push_back(paragraph);
    d.push_back(sentence_no);

}

Node* SearchEngine::search(string pattern, int &n_matches){
    
    Node* root=NULL;
    int x=0;
    for(auto i : v){
    searchpat(root,pattern,i,x,a,b,c,d);
    x++;
    }
    int count=0;
    Node* temp=root;
    while(temp!=NULL){
        count++;
        temp=temp->right;
    }
    n_matches=count;
    return root;
}

// int main(){
//     SearchEngine* s = new SearchEngine();
//     s->insert_sentence(1,1,1,1,"ababa");
//     int r=0;
//     s->search("abA",r);
//     cout<<r<<endl;
// }