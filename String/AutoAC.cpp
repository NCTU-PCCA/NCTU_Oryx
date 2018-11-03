#include <iostream>
#include <string.h>
#include <map>
#include <queue>
using namespace std;
int cnt[155];
//---codebook test=String/AC
//---codebook start
#define MAXN 1000005
template<typename T>
struct AutoAC{
	struct Node {
		int v;
		map<T, Node*> ch;
		typename map<T, Node*>::iterator find(T k){ return ch.find(k); }
		typename map<T, Node*>::iterator begin(){ return ch.begin(); }
		typename map<T, Node*>::iterator end(){ return ch.end(); }
		Node *at(T k){ return ch.at(k); }
		Node *& operator [](T k){ return this->ch[k]; }
		void insert(T k, Node* v){ ch.insert(pair<T, Node*>(k, v)); }

		Node *fail;
	} nodes[MAXN];
	int n;
	Node *root;
	Node *newNode(){ nodes[n].v=0; nodes[n].fail=nullptr; nodes[n].ch.clear(); return nodes+(n++); }
	AutoAC() { n=0; root=newNode(); root->v=0; root->fail=nullptr; }
	void init() { n=0; root=newNode(); root->v=0; root->fail=nullptr; }

	void insert( const T *s , int k ) {
		Node *now = root;
		for(int i=0; s[i]; i++){
			typename map<T, Node*>::iterator it = now->find(s[i]);
			if(it == now->end()){
				now->insert(s[i], newNode());
			}
			now = now->at(s[i]);
		}
		now->v = k;
	}
	void buildFail() {
		queue<Node*> q;
		q.push(root);
		while(!q.empty()) {
			Node *x = q.front(); q.pop();
			for(typename map<T, Node*>::iterator it = x->begin(); it!=x->end(); it++){
				T next = it->first;
				Node *cur = x->fail;
				while(cur&&cur->find(next) == cur->end())cur = cur->fail;
				it->second->fail = cur ? cur->at(next) : root;
				q.push(it->second);
			}
		}
	}
	int search( const T *s ) {
		int res=0;
		Node *cur = root;
		for(int i=0; s[i]; i++){
			while(cur && cur->find(s[i]) == cur->end())cur = cur->fail;
			cur = cur ? cur->at(s[i]) : root;
			if(cur->v)cnt[cur->v]++;
			res = max(cnt[cur->v], res);
		}
		return res;
	}
};
//---codebook end

AutoAC<char> AC;
char s[155][100];
int len[155];
char t[1000005];
int n;
int main() {
	while(scanf("%d", &n) == 1) {
		if(!n)break;
		AC.init();
		for(int i=1; i<=n; i++)len[i] = cnt[i] = 0;
		for(int i=1; i<=n; i++) {
			scanf("%s", s[i]);
			len[i] = strlen(s[i]);
			AC.insert(s[i], i);
		}
		AC.buildFail();
		scanf("%s", t);
		int ans = AC.search(t);
		printf("%d\n", ans);
		for(int i=1; i<=n; i++) {
			if(cnt[i] == ans)printf("%s\n", s[i]);
		}
	}
	return 0;
}
