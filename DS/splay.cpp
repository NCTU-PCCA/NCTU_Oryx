#include <stdio.h>
#include <iostream>

using namespace std;

//---codebook start
#define MAXN 200005
#define SZ(o) (o?(o->sz):0)
#define MI(o) (o?(o->minv):2147483647)

struct Node {
	int v,sz;
	int add, minv, rev;
	Node *ch[2];
}NODES[MAXN];
int nodecnt;
Node *newNode() {
	NODES[nodecnt].v=NODES[nodecnt].add=NODES[nodecnt].minv=0;
	NODES[nodecnt].rev = 0;
	NODES[nodecnt].sz=1;
	NODES[nodecnt].ch[0] = NODES[nodecnt].ch[1] = NULL;
	return NODES + (nodecnt++);
}
Node *newNode(int x) { Node *res = newNode(); res->minv = res->v = x; return res; }

void push(Node *&o) {
	if(!o)return ;
	if(o->rev) {
		o->rev = 0;
		swap(o->ch[0], o->ch[1]);
		if(o->ch[0])o->ch[0]->rev ^= 1;
		if(o->ch[1])o->ch[1]->rev ^= 1;
	}
	if(o->add) {
		o->minv += o->add;
		o->v += o->add;
		if(o->ch[0])o->ch[0]->add += o->add;
		if(o->ch[1])o->ch[1]->add += o->add;
		o->add = 0;
	}
}
void pull(Node *&o) {
	if(!o)return ;
	push(o);
	push(o->ch[0]); push(o->ch[1]);
	o->sz = 1;
	o->sz += SZ(o->ch[0]) + SZ(o->ch[1]);
	o->minv = min(o->v, min(MI(o->ch[0]), MI(o->ch[1])));
}
void rotate(Node *&o, int d) {
	push(o);
	Node *c = o->ch[d^1];
	//cout<<o<<" "<<c<<" "<<o->v<<" "<<c->v<<endl;
	push(c);
	o->ch[d^1] = c->ch[d];
	c->ch[d] = o; 
	pull(o); pull(c);
	o = c;
}
void splay(Node *&o, int k) {
	if(!o)return ;
	push(o);
	int i = SZ(o->ch[0]) + 1;
	int d1, d2;
	Node *p;
	//cout<<i<<" "<<k<<endl;
	//cout<<o<<" "<<o->ch[0]<<" "<<o->ch[1]<<endl;
	if(i == k)return ;
	else if(i < k) {
		k -= i;
		d1 = 0;
		p = o->ch[1];
	} else {
		d1 = 1;
		p = o->ch[0];
	}
	push(p);
	i = SZ(p->ch[0]) + 1;
	//cout<<"sec "<<i<<" "<<k<<endl;
	if(i == k){ rotate(o, d1); return ;}
	else if(i < k) {
		k -= i;
		d2 = 0;
		splay(p->ch[1], k);
	} else {
		d2 = 1;
		splay(p->ch[0], k);
	}
	if(d1^d2) { rotate(o->ch[d1^1], d2); rotate(o, d1); }
	else { rotate(o, d1); rotate(o, d2); }
	pull(o);
}
void split(Node *o, int x, Node *&l, Node *&r) {
	if(x == 0) { l = NULL; r = o; return ; }
	push(o);
	splay(o, x);
	r = o->ch[1];
	o->ch[1] = NULL;
	l = o;
	pull(l); pull(r);
}
void merge(Node *&l, Node *r) {
	//cout<<"l->sz: "<<SZ(l)<<endl;
	if(!l){ l = r; return ; }
	splay(l, SZ(l));
	//cout<<"l r "<<SZ(l)<<" "<<SZ(r)<<endl;
	l->ch[1] = r;
	pull(r); pull(l);
}
//---codebook end

void buildST(Node *o) {
	if(!o)return ;
	push(o);
	buildST(o->ch[0]);
	cout<<o->v<<" ";
	buildST(o->ch[1]);
}

int n;
int main()
{
	while(scanf("%d", &n) == 1) {
		Node *root = NULL;
		nodecnt = 0;
		for(int i=0; i<n; i++) {
			int x;
			scanf("%d", &x);
			//cout<<SZ(root)<<endl;
			Node *node = newNode(x);
			merge(root, node);
			//cout<<SZ(root)<<endl;
		}
		int m;
		scanf("%d", &m);
		for(int i=0; i<m; i++) {
			char com[10];
			int x,y,d;
			scanf("%s", com);
			Node *l, *m, *r;
			if(com[0] == 'A') {
				scanf("%d%d%d", &x, &y, &d);
				split(root, x-1, l, m);
				split(m, y-x+1, m, r);
				//cout<<"add "<<m->v<<" "<<SZ(m)<<endl;
				m->add += d;
				merge(m, r);
				merge(l, m);
				root = l;
			} else if(com[0] == 'I') {
				scanf("%d%d", &x, &y);
				split(root, x, l, r);
				merge(l, newNode(y));
				merge(l, r);
				root = l;
			} else if (com[0] == 'D') {
				scanf("%d", &x);
				split(root, x-1, l, m);
				split(m, 1, m, r);
				//buildST(l); puts("");
				//buildST(m); puts("");
				//buildST(r); puts("");
				merge(l, r);
				root = l;
			} else if (com[0] == 'M') {
				scanf("%d%d", &x, &y);
				split(root, x-1, l, m);
				split(m, y-x+1, m, r);
				//cout<<"hi";
				printf("%d\n", m->minv);
				merge(m, r);
				merge(l, m);
				root = l;
			} else if (com[3] == 'E') {
				scanf("%d%d", &x, &y);
				split(root, x-1, l, m);
				split(m, y-x+1, m, r);
				m->rev ^= 1;
				merge(m, r);
				merge(l, m);
				root = l;
			} else if (com[3] == 'O') {
				scanf("%d%d%d", &x, &y, &d);
				split(root, x-1, l, m);
				split(m, y-x+1, m, r);
				d%=SZ(m);
				Node *rm;
				split(m, SZ(m) - d, m, rm);
				merge(rm, m); m = rm;
				merge(m, r);
				merge(l, m);
				root = l;
			}
			//buildST(root);
			//puts("");
		}
	}
	return 0;
}
