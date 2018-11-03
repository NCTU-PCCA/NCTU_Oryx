#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
//---codebook test=Flow/MCF
//---codebook start
#define ll long long int 
#define LINF 214748364700000LL
#define INF 2147483647
using namespace std;
struct MCF {
	struct edge
	{
		int u, v, c, f;
		ll co;
		edge(int _u, int _v, int _c, ll _co){ u = _u, v = _v, c = _c; co = _co; f = 0; }
	};
	vector<vector<int> > G;
	vector<edge> E;
	vector<ll> d;
	vector<int> inq, arg, p;
	int N, s, t;
	MCF(int _n) {
		N = _n;
		G.resize(_n+1);
		d.resize(_n+1); inq.resize(_n+1);
		arg.resize(_n+1); p.resize(_n+1);
		E.clear();
	}
	void pb(int u, int v, int c, ll co) {
		G[u].push_back(E.size());
		E.push_back(edge(u, v, c, co));
		G[v].push_back(E.size());
		E.push_back(edge(v, u, 0, -co));
	}
	bool BF(int &flow, ll &cost) {
		for(int i=0;i<=N;i++)p[i] = 0, inq[i] = 0, d[i] = LINF;
		queue<int> Q;
		Q.push(s);
		d[s]=0; inq[s] = 1; arg[s] = INF;
		while(!Q.empty()) {
			int x=Q.front(); Q.pop(); inq[x] = 0;
			for(int i=0; i<(int)G[x].size(); i++) {
				edge &e=E[G[x][i]];
				if(d[x] + e.co < d[e.v] && e.c > e.f) {
					d[e.v] = d[x]+e.co;
					p[e.v] = G[x][i];
					arg[e.v] = min(arg[x], e.c - e.f);
					if(!inq[e.v])Q.push(e.v), inq[e.v] = 1;
				}
			}
		}
		if(d[t] == LINF)return 0;
		int a = arg[t];
		for(int now = t; now != s; now = E[p[now]].u) {
			E[p[now]].f += a;
			E[p[now]^1].f -= a;
		}
		cost += arg[t] * d[t];
		flow += a;
		return 1;
	}

	pair<int, ll> operator ()(int _s, int _t) {
		s = _s, t = _t;
		int flow=0;
		ll cost=0;
		while(BF(flow, cost)){}
		return pair<int, ll>(flow, cost);
	}
};
//---codebook end

int main()
{
	int n, m;
	MCF mcf(105);
	while(scanf("%d", &n) == 1) {
		if(!n)break;
		for(int i=0; i<=n+1; i++) {
			mcf.G[i].clear();
		}
		mcf.E.clear();
		scanf("%d", &m);
		for(int i=0; i<m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			mcf.pb(u, v, 1, w);
			mcf.pb(v, u, 1, w);
		}
		mcf.pb(0, 1, 2, 0);
		mcf.pb(n, n+1, 2, 0);
		pair<int, ll> ans = mcf(0, n+1);
		if(ans.first == 2) {
			printf("%lld\n", ans.second);
		} else {
			puts("Back to jail");
		}
	}
	return 0;
}
