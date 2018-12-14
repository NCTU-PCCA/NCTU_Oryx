#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

//---codebook test=Math/mobius
/*---codebook desc
Given ${p_n}$ be a sequence of distinct primes:
$$
\mu(x)=
\begin{cases}
	1, &\text{if $x=p_1p_2...p_k$, $k$ is even }\\
	-1, &\text{where $k$ above is odd}\\
	0, &\text{if $x$ is not square free}
\end{cases}
$$
*/

//---codebook start
#define ll long long int
#define MAXN 1000005

ll n;
int isp[1000005];
int mu[1000005];
vector<ll> p;

void sieve() {
	for(int i=0; i<MAXN; i++) isp[i] = 1;
	isp[0] = isp[1] = 0;
	mu[1] = 1;
	for(ll i=2; i<MAXN; i++) {
		if(isp[i]){
			p.push_back(i);
			mu[i] = -1;
		}
		for(int j=0; j<(int)p.size() && i*p[j] < MAXN; j++) {
			ll x = p[j] * i;
			isp[x] = 0;
			if(i % p[j] == 0) {
				mu[x] = 0;
				break;
			}
			mu[x] = -mu[i];
		}
	}
}
//---codebook end

int main() { 
	sieve();
	for(int i=1; i<=1000; i++)printf("%d\n", mu[i]);
	return 0;
}
