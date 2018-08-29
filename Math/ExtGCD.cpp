#include <stdio.h>
#include <iostream>

//---codebook test=Math/extgcd
//---codebook start
typedef long long int ll;
#define mod 1000000007
void gcd(ll a, ll b, ll &x, ll &y, ll &d) {
	if(!b){ x = 1; y = 0; d = a; return ; }
	gcd(b, a%b, y, x, d); y -= (a/b)*x;
}
ll inv(ll a) {
	ll x, y, d;
	gcd(a, mod, x, y, d);
	return d==1 ? (x+mod)%mod : 0;
}
//---codebook end

int main() {
	ll x;
	while(scanf("%lld", &x) == 1) {
		printf("%lld\n", inv(x));
	}
	return 0;
}
