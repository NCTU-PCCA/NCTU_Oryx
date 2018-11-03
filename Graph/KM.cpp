#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//---codebook start
#define MAXN 1005
#define LL __int128_t
int t,N,K;
LL w[MAXN][MAXN];
LL x[MAXN],y[MAXN];
LL Lx[MAXN],Ly[MAXN];
bool S[MAXN],T[MAXN];
int Left[MAXN];
LL U,L;
const LL INF=(((LL)0x7fffffffffffffLL)<<50)|((LL)0xffffffffffffffffLL);

void getLL(LL &x){
	x=0;
	char c=getchar();
	while(c>'9'||c<'0')c=getchar();
	while(c<='9'&&c>='0'){x*=(LL)10;x+=(LL)(c-'0');c=getchar();}
}
void printLL(LL x){
	if(!x){printf("0"); return ;}
	vector<int> res;
	while(x) {
		res.push_back((int)(x%10));
		x/=(LL)10;
	}
	for(int i=res.size()-1;i>=0;i--)printf("%d",res[i]);
}

void initKM(){
	for(int i=1;i<=N;i++) {
		S[i]=T[i]=false;
		Left[i]=0;
		Lx[i]=Ly[i]=(LL)0LL;
		for(int j=1;j<=N;j++){
			if(w[i][j]==-INF)continue;
			if(x[i]+y[j]>U) {
				w[i][j]=L-U;
			} else if(x[i]+y[j]>L) {
				w[i][j]=L-x[i]-y[j];
			} else w[i][j]=0;
		}
	}
}

bool dfs(int i){
	S[i]=true;
	for(int j=1;j<=N;j++) {
		if(T[j])continue;
		if(Lx[i]+Ly[j]==w[i][j]) {
			T[j]=true;
			if(!Left[j]||dfs(Left[j])) {
				Left[j]=i;
				return true;
			}
		}
	}
	return false;
}

void KM(LL &ANS){
	for(int i=1;i<=N;i++){
		while(true) {
			for(int j=1;j<=N;j++)S[j]=T[j]=0;
			if(dfs(i))break;

			LL d=INF;
			for(int x=1;x<=N;x++){
				if(S[x])
				for(int y=1;y<=N;y++){
					if(!T[y]&&w[x][y]!=-INF)d=min(d,Lx[x]+Ly[y]-w[x][y]);
				}
			}
			if(d==INF){ANS=INF; return ;}

			for(int i=1;i<=N;i++){
				if(S[i])Lx[i]-=d;
				if(T[i])Ly[i]+=d;
			}
		}
	}

	for(int i=1;i<=N;i++) {
		ANS-=w[Left[i]][i];
	}
}

int main(){
	//cout<<INF*2<<endl;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&N);
		getLL(L);getLL(U);
		scanf("%d",&K);
		for(int i=0;i<=N;i++)for(int j=0;j<=N;j++)w[i][j]=0;
		for(int i=0;i<K;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			w[u][v]=-INF;
		}
		for(int i=1;i<=N;i++)getLL(x[i]);
		for(int i=1;i<=N;i++)getLL(y[i]);
		initKM();
		LL ANS=0;
		KM(ANS);
		if(ANS==INF)puts("no");
		else printLL(ANS),puts("");
	}
	return 0;
}
//---codebook end
