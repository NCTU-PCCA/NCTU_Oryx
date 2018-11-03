#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

//---codebook start
#define MAXN 100005
int N;
bool vis[MAXN];
vector<int> G[MAXN];
vector<int> R[MAXN];
vector<int> SCC[MAXN];
int sccno[MAXN];
int scc_cnt;
int owner[MAXN];
int dfs_stamp;

queue<int> Q;
void dfs_for_stamp(int now) {
	vis[now]=true;
	for(int i=0;i<(int)R[now].size();i++)
	{
		int v=R[now][i];
		if(!vis[v]) {
			dfs_for_stamp(v);
		}
	}
	owner[++dfs_stamp]=now;
}

void dfs_for_scc(int now) {
	vis[now]=true;
	sccno[now]=scc_cnt;
	SCC[scc_cnt].push_back(now);
	for(int i=0;i<(int)G[now].size();i++)
	{
		int v=G[now][i];
		if(!vis[v])dfs_for_scc(v);
	}
}

int main() {
	dfs_stamp=0;
	for(int i=1;i<=N;i++) {
		owner[i]=0;
	}
	for(int i=1;i<=N;i++)if(!vis[i])dfs_for_stamp(i);
	for(int i=1;i<=N;i++)vis[i]=false;
	scc_cnt=0;
	for(int i=dfs_stamp;i>=1;i--) {
		if(!vis[owner[i]]){//cout<<i<<" "<<owner[i]<<endl;
			dfs_for_scc(owner[i]),scc_cnt++;
		}
	}
    return 0;
}
//---codebook end
