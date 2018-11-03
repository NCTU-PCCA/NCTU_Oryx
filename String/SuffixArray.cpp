#include <stdio.h>
#include <iostream>
#include <string.h>
#include <set>

using namespace std;

//---codebook test=String/SA
//---codebook start
#define SIGSZ 130
#define MAXN 1000005
struct SA {
	int c[MAXN];
	int r1[MAXN], r2[MAXN], sa[MAXN], h[MAXN];
	int *rx = r1, *y = r2;
	int neq(int *r, int a, int b, int step, int n){
		return r[a] != r[b] || a+step>=n || b+step>=n || r[a+step] != r[b+step]; 
	}
	void build(int *s, int n, int *_rank, int *_hei, int *_h) {
		for(int i=0; i<SIGSZ; i++) c[i] = 0;
		for(int i=0; i<n; i++)c[rx[i] = s[i]]++;
		for(int i=1; i<SIGSZ; i++)c[i] = c[i-1] + c[i];
		for(int i=n-1; i>=0; i--)sa[--c[s[i]]] = i;
		int m = SIGSZ, p = 0;
		for(int step = 1; step<n; step<<=1, p=0) {
			// storing index of rx[i] based on sorted y[i] to y[i],
			// using the previously calculated sa[i] array.
			for(int i=n-step; i<n; i++)y[p++] = i;
			for(int i=0; i<n; i++)if(sa[i] >= step)y[p++] = sa[i] - step;
			// sorting rx[i] in the order of sorted y[i](aka. rx[y[i]])
			for(int i=0; i<m; i++)c[i] = 0;
			for(int i=0; i<n; i++)c[rx[y[i]]]++;
			for(int i=1; i<m; i++)c[i] = c[i-1] + c[i];
			for(int i=n-1; i>=0; i--)sa[ --c[rx[y[i]]] ] = y[i];
			m = 1; swap(rx, y); rx[sa[0]] = 0;
			for(int i=1; i<n; i++)rx[sa[i]] = neq(y, sa[i], sa[i-1], step, n) ? m++ : m-1;
			if(m == n) break;
		}
		int ph = 0;
		for(int i=0; i<n; i++) h[i] = 0;
		for(int i=0; i<n; i++) {
			if(rx[i] == 0) { h[i] = 0; continue; }
			if(i == 0 || h[i-1] <= 1) {
				for(ph = 0; i+ph<n && s[i+ph] == s[sa[rx[i]-1] + ph]; ph++);
			} else {
				for(ph = h[i-1]-1; i+ph<n && s[i+ph] == s[sa[rx[i]-1] + ph]; ph++);
			}
			h[i] = ph;
		}
		if(_rank){ for(int i=0; i<n; i++)_rank[i] = rx[i]; }
		if(_hei){ for(int i=0; i<n; i++)_hei[i] = h[sa[i]]; }
		if(_h){ for(int i=0; i<n; i++)_h[i] = h[i]; }
	}
	inline int operator [](int i){ return sa[i]; }
};
//---codebook end

char s[102205];
int ns[102205];
int st[MAXN];
SA sa;
int rk[MAXN], hei[MAXN], h[MAXN];
int n;

int test(int x, int len, int print) {
	set<int> vis;
	if(x == 0)return 1;
	int cnt = 0, f = 0;
	for(int i=1; i<len; i++) {
		if(hei[i] < x){ f = cnt = 0; vis.clear(); continue; }
		if(st[sa[i]] != st[sa[i-1]] && vis.find(st[sa[i]]) == vis.end()){
			if(cnt == 0)vis.insert(st[sa[i-1]]);
			vis.insert(st[sa[i]]); cnt++;
		}
		if(2*(cnt + 1) > n){
			if(!print)return 1;
			if(!f){
				f = 1;
				for(int j=sa[i]; j<sa[i]+x; j++)printf("%c", s[j]);
				puts("");
			}
		}
	}
	return 0;
}

int main() {
	int kase = 0;
	while(scanf("%d", &n) == 1) {
		if(!n)break;
		int len = 0;
		for(int i=0; i<n; i++) {
			scanf("%s", s+len);
			int sl = strlen(s+len);
			for(int j=0; j<sl; j++)ns[len+j] = s[len+j]-'a'+1,st[len+j] = i+1;
			st[len+sl] = 0;
			ns[len+sl] = 0;
			len += sl; 
			if(i == n-1)break;
			ns[len] = 26 + i + 1;
			s[len] = '.';
			len++;
		}
		sa.build(ns, len, rk, hei, h);
		//printf("%s\n", s);
		//for(int i=0; i<len; i++)printf(" %d", sa[i]);puts("");
		//for(int i=0; i<len; i++)printf("%s\n", s+sa[i]);
		//for(int i=0; i<len; i++)printf("%d ", hei[i]);puts("");
		int l=0, r = len;
		while(l < r) {
			int mid = (l+r)>>1;
			if(test(mid, len, 0))l = mid+1;
			else r = mid;
		}
		if(kase++)puts("");
		if(n == 1)printf("%s\n", s);
		else if(l == 1)puts("?");
		else test(l-1, len, 1);
	}
	return 0;
}
