#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//---codebook test=Flow/dinic
//---codebook start
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3fLL
struct Dinic {
	typedef long long int T;
	struct edge{
		int u, v;
		T c, f;
		edge(int _u, int _v, T _c, T _f): u(_u),v(_v),c(_c),f(_f){}
	};
	int n, s, t;
	vector<vector<int> > G;
	vector<edge> E;
	vector<int> cur, vis, d;
	Dinic(int _n):n(_n){
		G.resize(n+1);
		vis.resize(n+1); cur.resize(n+1); d.resize(n+1);
		for(int i=0; i<=n; i++)d[i] = INF;
	}
	void pb(int u, int v, T cap){
		G[u].push_back(E.size());
		E.push_back(edge(u, v, cap, 0));
		G[v].push_back(E.size());
		E.push_back(edge(v, u, 0, 0));
	}
	int bfs() {
		queue<int> q;
		for(int i=0; i<=n; i++)vis[i] = 0;
		q.push(s); d[s] = 0;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = 1;
			for(int i=0; i<(int)G[u].size(); i++) {
				edge e = E[G[u][i]];
				if(e.c - e.f > 0 && !vis[e.v]) {
					d[e.v] = d[u] + 1;
					q.push(e.v);
				}
			}
		}
		return vis[t];
	}
	T dfs(int u, T a) {
		if(u == t || !a)return a;
		T totf = 0, f;
		for(int &i=cur[u]; i<(int)G[u].size(); i++) {
			edge &e = E[G[u][i]], &r=E[G[u][i]^1];
			if(d[e.v] != d[u]+1)continue;
			f = dfs(e.v, min(a, e.c - e.f));
			if(f<=0)continue;
			e.f += f; r.f -= f;
			totf += f;
			a -= f; if(!a)break;
		}
		return totf;
	}

	T operator()(int _s, int _t) {
		s = _s, t = _t;
		T maxf = 0;
		while(bfs()) {
			for(int i=0; i<=n; i++)cur[i] = 0;
			maxf += dfs(s, LINF);
		}
		return maxf;
	}
};
//---codebook end

int main()
{
	int n, m, s, t;
	int nt = 0;
	while(scanf("%d", &n) == 1) {
		nt++;
		if(!n)break;
		Dinic dinic(n);
		scanf("%d%d%d", &s, &t, &m);
		for(int i=0; i<m; i++){
			int u,v; long long int cap;
			scanf("%d%d%lld", &u, &v, &cap);
			dinic.pb(u, v, cap);
			dinic.pb(v, u, cap);
		}
		long long int ans = dinic(s,t);
		printf("Network %d\nThe bandwidth is %lld.\n\n", nt, ans);
	}
}
