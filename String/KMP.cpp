#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;
//---codebook test=String/KMP
//---codebook start
char s[10005], t[10005];
int f[10005];
// t is 1-based
void buildFail() {
	f[1]=0; f[0]=-1;
	for(int i=2; t[i]; i++){
		int now = f[i-1];
		while(now!=-1 && t[now+1] != t[i])now = f[now];
		f[i] = now+1;
	}
}

int search(char *s, int m) {
	int now = 0, res = 0;
	for(int i=0; s[i]; i++){
		while(now!=-1 && s[i] != t[now+1]) now = f[now];
		now++; 
		if(now == m)res++;
	}
	return res;
}
//---codebook end

int main()
{
	int n,q;
	scanf("%d", &n);
	while(n--){
		scanf("%s", s);
		scanf("%d", &q);
		for(int i=0; i<q; i++){
			scanf("%s", t+1);
			buildFail();
			int len = strlen(t+1);
			//cout << len <<endl;
			int ans = search(s, len);
			printf("%d\n", ans);
		}
	}
	return 0;
}
