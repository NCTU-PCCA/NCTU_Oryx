#include <stdio.h>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

#define MAXN 100005

int n, m;
char c[MAXN];
char t[MAXN];
int need;
//---codebook start
vector<int> G[MAXN], scc[MAXN];
vector<int> stk;
int clk, scnt;
int low[MAXN], pre[MAXN], ins[MAXN];

void dfs(int u) {
	ins[u] = 1;
	stk.push_back(u);
	low[u] = pre[u] = ++clk;
	for(int i=0; i<(int)G[u].size(); i++) {
		int v = G[u][i];
		if(!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if(ins[v]) {
			low[u] = min(low[u], pre[v]);
		}
	}
	if(low[u] == pre[u]) {
		scnt++;
		while(stk.size() && stk.back() != u) {
			scc[scnt].push_back(stk.back());
			ins[stk.back()] = 0;
			stk.pop_back();
		}
		if(stk.size() && stk.back() == u) {
			scc[scnt].push_back(u);
			stk.pop_back();
			ins[u] = 0;
		}
	}
}
//---codebook end

int main() {
	scanf("%d%d", &n, &m);
	clk = 0;
	scanf("%s", c+1);
	for(int i=0; i<m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
	}
	scanf("%s", t);
	need = 0;
	int check = 0;
	for(int i=0; t[i]; i++)need |= (1<< (t[i]-'a'));
	for(int i=1; i<=n; i++) {
		if(!pre[i]) {
			dfs(i);
			if(check)break;
		}
	}
	if(check)puts("Yes");
	else puts("No");
	return 0;
}
