#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

//---codebook start
#define MAXN 100005
#define LL long long int

using namespace std;

int N,M,Q;
LL V[MAXN];
LL S[MAXN];
int A[MAXN];
int ANS[MAXN];

struct query
{
    int l,r,id;LL c;
    bool operator <(const query &r)const{
        return l<r.l;
    }
};

vector<query> QUERIES;
vector<int> FARM[MAXN];
int nxt[MAXN];

LL BIT[MAXN];
void bit_add(int pos,LL v){while(pos<=MAXN)BIT[pos]+=v,pos+=(pos&(-pos));}
LL bit_query(int pos){LL res=0;while(pos>0)res+=BIT[pos],pos-=(pos&(-pos));return res;}

void tot_bs(int s,int e,vector<int>& people)
{
    //cout<<s<<" "<<e<<endl;
    if(s==e){for(auto p:people)ANS[p]=s;return ;}
    vector<query> queries;
    vector<int> farms;
    int mid=(s+e)/2;
    for(int i=0;i<people.size();i++)
    {
        //cout<<"YEE "<<i<<endl;
        int p=people[i];
        for(int j=0;j<FARM[p].size();j++)
        {
            //cout<<"YEE2 "<<j<<endl;
            farms.push_back(FARM[p][j]);
        }
    }
    for(int i=s;i<=mid;i++)
    {
        queries.push_back(QUERIES[i]);
    }
    sort(farms.begin(),farms.end());
    sort(queries.begin(),queries.end());
    map<int,LL> changes;
    int k=0;
    for(auto f:farms)
    {
        for(k;k<queries.size()&&f>=queries[k].l;k++)bit_add(queries[k].r,queries[k].c);
        LL change=bit_query(nxt[f]-1)-bit_query(f-1);
        S[A[f]]+=change;
        if(changes.find(A[f])==changes.end())changes[A[f]]=change;
        else changes[A[f]]+=change;
    }
    vector<int> finished,notyet;
    for(auto p:people)
    {
        if(S[p]>=V[p])finished.push_back(p),S[p]-=changes[p];
        else notyet.push_back(p);
    }
    for(k=k-1;k>=0;k--)bit_add(queries[k].r,-queries[k].c);
    tot_bs(s,mid,finished);
    tot_bs(mid+1,e,notyet);
}

int main()
{
    while(scanf("%d%d%d",&N,&M,&Q)==3)
    {
        vector<int> people;
        for(int i=1;i<=M;i++)
        {
            scanf("%d",A+i);
            FARM[A[i]].push_back(i);
        }
        for(int i=1;i<=N;i++)
        {
            people.push_back(i);
            for(int j=0;j<FARM[i].size();j++)
            {
                nxt[FARM[i][j]]=(j+1==FARM[i].size() ? M+1 : FARM[i][j+1]);
            }
            scanf("%lld",V+i);
        }
        for(int i=0;i<Q;i++)
        {
            int l,r;LL c;
            scanf("%d%d%lld",&l,&r,&c);
            QUERIES.push_back((query){l,r,i,c});
        }
        tot_bs(0,Q,people);
        for(int i=1;i<=N;i++)
        {
            printf("%d\n",ANS[i]==Q?-1:ANS[i]+1);
        }
    }
    return 0;
}
//---codebook end
