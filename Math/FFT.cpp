#include <stdio.h>
#include <iostream>
//---codebook flag=--std=c++11
/*---codebook desc
\begin{enumerate}
\itemsep-0.5em
\item When convert back to integer, use \lstinline{LL} can be safer.
\item \lstinline{eps} are \lstinline{0.5} generally, but sometime need adjustments.
\item the array \lstinline{A} and \lstinline{B} will be changed after DFT, and the result \lstinline{AB} has been devided by \lstinline{_n}.
\end{enumerate}
*/
//---codebook test=Math/FFT
//---codebook start
#include <stdlib.h>
#include <math.h>
#include <complex>
#include <string.h>
#define MAXN 1048576
#define eps 0.5
#define PI 3.141592653589793238462643383279502884197169399375
#define max(a,b) (((a) > (b)) ? (a) : (b))

typedef std::complex<double> comp;

struct FFT{
	int _n;
	comp ww[MAXN], rw[MAXN];
	void init(int n, int m){ // n terms in polynomial
		_n=1; while(_n<n+m)_n<<=1;
		ww[0] = rw[0] = comp(1.0, 0.0);
		for(int k=1; k<_n; k++){
			ww[k]=comp(cos(2*k*PI/_n), sin(2*k*PI/_n));
			rw[_n-k]=ww[k];
		}
	}
	int rev(int n,int x){int res=0;while(n){res<<=1;res|=x&1;x>>=1;n>>=1;}return res;}
	void dft(int n, comp *res, comp *w){
		for(int i=0; i<n; i++){int j=rev(n>>1,i);if(i<j){comp tmp=res[j];res[j]=res[i];res[i]=tmp;}}
		for(int m=1; m<=n; m<<=1){ 
			if(m==1)continue;
			int mp = m>>1;
			for(int o = 0; o<n; o+=m){
				for(int i=0; i<mp; i++){
					comp tmp = w[i*(n/m)]*res[o+i+mp];
					res[o+i + mp] = res[o+i] - tmp;
					res[o+i] = res[o+i] + tmp;
				}
			}
		}
	}

	void mult(comp *A, comp *B, comp *AB){
		dft(_n, A, ww); dft(_n, B, ww);
		for(int i=0; i<_n; i++)AB[i] = A[i]*B[i];
		dft(_n, AB, rw);
		for(int i=0; i<_n; i++)AB[i]/=_n;
	}
} fft;

comp A[MAXN], B[MAXN];
comp AB[MAXN];
//---codebook end
int cnt[MAXN];
int isp[MAXN];
using namespace std;

int main() {
	int T;
	for(int i=0; i<500005; i++)cnt[i] = 1, isp[i] = 1;
	cnt[0] = 0;
	isp[1] = 0;
	for(int i=1; i<500005; i++) {
		if(isp[i]) {
			cnt[i]++;
			for(int j=2*i; j<500005; j+=i) {
				isp[j] = 0;
				int t = j, p = 0;
				while(t%i==0)p++, t/=i;
				cnt[j] *= (p+1);
			}
		}
	}
	fft.init(500000, 500000);
	for(int i=0; i<500005; i++)A[i] = B[i] = comp(cnt[i], 0.0);
	fft.mult(A, B, AB);
	//for(int i=0; i<500000; i++)cout<<(long long int)(real(AB[i])+eps)<<" ";cout<<endl;
	//return 0;
	while(scanf("%d", &T)==1) {
		while(T--) {
			int l, r;
			scanf("%d%d", &l, &r);
			int ansi = -1; int ans = 0;
			for(int i=r; i>=l; i--) {
				if((int)(real(AB[i])+eps) >= ans) { 
					ans = (int)(real(AB[i]+eps));
					ansi = i;
				}
			}
			printf("%d %d\n", ansi, ans);
		}
	}

	return 0;
}
