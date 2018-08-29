#include<iostream>
#include <stdio.h>
//---codebook test=Graph/cutbcc
/*---codebook desc
\paragraph{Determining Bridge}
$low[v] > pre[u] \Rightarrow v$ is a cut vertex and $(u,v)$ is a bridge
*/
//---codebook start
#include <stack>
#include <queue>
#include <vector>
#define MAXN 1005
using namespace std;
struct edge {
	int u,v;
	edge(int _u,int _v){u=_u;v=_v;}
};
vector<edge> E;
vector<int> G[MAXN];
int N,M;
void pb(int u,int v) {
	G[u].push_back(E.size());
	E.push_back(edge(u,v));
	G[v].push_back(E.size());
	E.push_back(edge(v,u));
}

stack<edge> S;
int pre[MAXN],low[MAXN],bccno[MAXN];
int iscut[MAXN];
int stamp,bcc_cnt;
vector<int> bcc[MAXN];

int dfs(int u,int fa) {
	low[u]=pre[u]=++stamp;
	int ch=0;
	iscut[u]=0;
	for(int i=0;i<(int)G[u].size();i++) {
		edge e=E[G[u][i]];
		int v=e.v;
		if(!pre[v]) {
			ch++;
			S.push(e);
			low[u]=min(low[u],dfs(v,u));
			if(low[v]>=pre[u]) {
				iscut[u]=true;
				bcc_cnt++;
				bcc[bcc_cnt].clear();
				while(1) {
					edge x=S.top();S.pop();
					if(bccno[x.u]!=bcc_cnt)bcc[bcc_cnt].push_back(x.u),bccno[x.u]=bcc_cnt;
					if(bccno[x.v]!=bcc_cnt)bcc[bcc_cnt].push_back(x.v),bccno[x.v]=bcc_cnt;
					if(x.u==u&&x.v==v)break;
				}
			}
		} else if(pre[v]<pre[u]&&v!=fa) {
			S.push(e);
			low[u]=min(low[u],pre[v]);
		}
	}
	if(fa<0&&ch==1)iscut[u]=false;
	return low[u];
}
//---codebook end

bool hate[MAXN][MAXN];
bool oddRing[MAXN];
int color[MAXN];
bool bipartite(int s,int b) {
    queue<int> Q;
    Q.push(s);
    color[s]=0;
    while(!Q.empty())
    {
        int x=Q.front();Q.pop();
        //cout<<"now is at "<<x<<" filling "<<color[x]<<endl;;
        for(int i=0;i<(int)G[x].size();i++)
        {
            edge &e=E[G[x][i]];
            int v=e.v;
            //cout<<v<<endl;
            if(bccno[v]!=b)continue;
            if(color[v]!=-1)
            {
                //cout<<v<<" visited "<<color[v]<<"\n";
                if(color[x]==color[v])return false;
            }
            else
            {
                //cout<<v<<" not visited\n";
                color[v]=color[x]==1 ? 0:1;
                Q.push(v);
            }
        }
        //puts("");
    }
    return true;
}

int main()
{
    while(scanf("%d%d",&N,&M)==2&&(N||M))
    {
        E.clear();
        for(int i=0;i<N;i++)
        {
            bccno[i]=pre[i]=0;
            oddRing[i]=false;
            G[i].clear();
            bcc[i].clear();
            for(int j=0;j<N;j++)hate[i][j]=false;
        }
        for(int i=0;i<M;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            u--,v--;
            hate[u][v]=hate[v][u]=true;
        }
        for(int i=0;i<N;i++)
        {
            for(int j=i+1;j<N;j++)
            {
                if(!hate[i][j])
                {
                    //printf("%d   %d\n",i+1,j+1);
                    pb(i,j);
                }
            }
        }
        int ans=0;
        stamp=bcc_cnt=0;
        for(int i=0;i<N;i++)if(!pre[i])dfs(i,-1);
        for(int i=1;i<=bcc_cnt;i++)
        {
            for(int j=0;j<N;j++)color[j]=-1;
            //cout<<i<<":"<<endl;
            for(int j=0;j<(int)bcc[i].size();j++)bccno[bcc[i][j]]=i; // deal with cut vertex
            //puts("");
            int s=bcc[i][0];
            if(!bipartite(s,i))for(int j=0;j<(int)bcc[i].size();j++)oddRing[bcc[i][j]]=true;
        }
        for(int i=0;i<N;i++)if(!oddRing[i])ans++;
        printf("%d\n",ans);
    }
    return 0;
}
