#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;
//---codebook test=Graph/MMC
/*---codebook desc
\paragraph{Remark}
The testcase of the snippet has been modified
*/
//---codebook start
#define MAXN 5005
#define INF 2147483647000
#define eps 1e-9
#define ll long long int

struct edge {
	int v; ll w;
	edge(int _v, ll _w){v=_v, w=_w;}
};

ll F[MAXN][MAXN];

double MMC(vector<vector<edge> > &G, int n) {
	double ans = 1e9;
	for(int i=0; i<n; i++) F[i][0] = 0;
	for(int i=0; i<n; i++) {
		for(int j=1; j<=n; j++) F[i][j] = INF;
	}
	for(int k=0; k<=n; k++) {
		for(int i=0; i<n; i++) {
			for(int j=0; j<(int)G[i].size(); j++) {
				edge &e = G[i][j];
				F[e.v][k+1] = min(F[e.v][k+1], F[i][k] + e.w);
			}
		}
	}
	for(int i=0; i<n; i++) {
		double tmp = 0;
		for(int k=0; k<n; k++) {
			tmp = max(tmp, (double)(F[i][n] - F[i][k])/(double)(n-k));
		}
		ans = min(ans, tmp);
	}
	return ans;
}
//---codebook end

int n, m;
vector<vector<edge> > G;

int main() {
	int T;
	scanf("%d", &T);
	for(int kase = 1; kase <= T; kase++) {
		scanf("%d%d", &n, &m);
		G.resize(n);
		for(int i=0; i<n; i++) G[i].clear();
		for(int i=0; i<m; i++) {
			int u, v;
			ll w;
			scanf("%d%d%lld", &u, &v, &w);
			u--, v--;
			G[u].push_back(edge(v, w));
		}
		double ans = MMC(G, n);
		if(ans-eps < 1e9 && 1e9 < ans+eps){printf("Case #%d: No cycle found.", kase); continue; }
		printf("Case #%d: %.2lf\n", kase, ans+eps);
	}
	return 0;
}
