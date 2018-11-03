#include<iostream>
#include<stdio.h>
#include<vector>
#include<queue>
#define MAXN 100000
#define INF 2147483646
using namespace std;
int inq[MAXN];
int cnt[MAXN];  //how many times passing vertex i
int d[MAXN];    //distances

struct edge
{
    int u,v,w;
};
vector<edge> edges;
vector<int> G[MAXN];

int N,M;

void BellmanFord(int s,int t)
{
    queue<int> Q;
    for(int i=0;i<=N;i++){inq[i]=0;d[i]=INF;cnt[i]=0;}
    d[s]=0;
    cnt[s]++;
    inq[s]=1;
    Q.push(s);
    while(!Q.empty())
    {
        int u=Q.front();Q.pop();inq[u]=0;
        for(auto i:G[u])
        {
            int v=edges[i].v,w=edges[i].w;
            if(d[u]<INF&&d[v]>d[u]+w)
            {
                d[v]=d[u]+w;

                if(!inq[v]){
                    Q.push(v);inq[v]=1;
                    if(++cnt[v]>N){d[t]=-INF;return ;}  //only when we need to travel this vertex , we check if it has ring
                }
            }
        }
    }
}

int main()
{
    while(scanf("%d%d",&N,&M)==2)
    {
        int u,v,w;
        for(int i=0;i<M;i++)
        {
            scanf("%d %d %d",&u,&v,&w);
            edges.push_back((edge){u,v,w});
            G[u].push_back(edges.size()-1);
        }
        int s,t;
        scanf("%d%d",&s,&t);
        BellmanFord(s,t);
        printf("%d\n",d[t]);
    }
    return 0;
}
