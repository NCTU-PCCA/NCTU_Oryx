#include <bits/stdc++.h>
using namespace std;
//---codebook start
struct LeftistTree{
	struct Node{
		int v, d;
		Node *l, *r;
		Node(int _v = 0){
			v = _v, d = 1;
			l = r = NULL;
		}
		inline int deep(){
			return d;
		}
		inline void pull(){
			if (!l) {l = r; r=NULL;return ;}
			if (l->deep() < r->deep())
				swap(l, r);
			d = 1 + r->deep();
		}
	}*rt;
	int sz;
	LeftistTree(){
		sz = 0; rt = NULL;
	}
	~LeftistTree(){
		remove(rt);
	}
	Node* merge(Node *L1, Node *L2){
		if (!L1 || !L2) return L1 ? L1 : L2;
		if (L1->v < L2->v){
			L1->r = merge(L1->r, L2);
			L1->pull();
			return L1;
		}else{
			L2->r = merge(L2->r, L1);
			L2->pull();
			return L2;
		}
	}
	void push(int v){
		rt = merge(rt, new Node(v));
		sz++;
	}
	void pop(){
		Node *tmp = rt;
		rt = merge(rt->l, rt->r);
		delete tmp;
		sz--;
	}
	void join(LeftistTree *L){
		rt = merge(rt, L->rt);
		L->rt = NULL;
		sz += L->sz;
		L->sz = 0;
	}
	int size(){ return sz; }
	int top(){ return rt->v; }
	bool empty(){ return !sz; }
	void remove(Node *u){ if (u) remove(u->l), remove(u->r), delete u; }
};
//---codebook end
const int MAXN = 1e5 + 5;
LeftistTree *sol[MAXN];
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int n, m; cin >> n >> m;
	for (int i = 0 ; i < n ; i++) sol[i] = new LeftistTree();
	while (m--){
		char input[20]; cin >> input;
		int a, b;
		switch (input[0]){
			case 'i':
				cin >> a >> b;
				sol[a-1]->push(b);
				break;
			case 'j':
				cin >> a >> b;
				sol[a-1]->join(sol[b-1]);
				break;
			case 'e':
				cin >> a;
				if (sol[a-1]->empty()) cout << "NULL" << endl;
				else{
					cout << sol[a-1]->top() << endl;
					sol[a-1]->pop();
				}
				break;
			case 'l':
				cin >> a;
				if (sol[a-1]->empty()) cout << "NULL" << endl;
				else cout << sol[a-1]->top() << endl;
				break;
		}
	}
	for (int i = 0 ; i < n ; i++) delete sol[i];
}
