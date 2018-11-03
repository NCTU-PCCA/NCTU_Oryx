#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>

using namespace std;

//---codebook test=Geometry/ConvexHull
//---codebook start
// Remember to check if the first point need to be repeated.
#define MAXN 100005
#define ll long long int
struct poi {
	ll x, y;
	bool operator <(const poi &rhs)const {
		return x == rhs.x ? (y < rhs.y) : (x < rhs.x);
	}
};
int test(poi &pi, poi &pj, poi &pk) {
	ll dx1 = pj.x - pi.x, dy1 = pj.y - pi.y;
	ll dx2 = pk.x - pi.x, dy2 = pk.y - pi.y;
	return dx1*dy2 - dx2*dy1 >= 0;
}
void ConvexHull(poi *po, int n, vector<poi> &hull) {
	vector<poi> p;
	for(int i=0; i<n; i++)p.push_back(po[i]);
	sort(p.begin(), p.end());
	hull.push_back(p[0]);
	for(int i=1; i<n; i++) {
		while(hull.size() > 1 && !test(hull[hull.size()-2], hull[hull.size()-1], p[i])) hull.pop_back();
		hull.push_back(p[i]);
	}
	unsigned int h1 = hull.size();
	for(int i=n-2; i>=0; i--) {
		while(hull.size() > h1 && !test(hull[hull.size()-2], hull[hull.size()-1], p[i])) hull.pop_back();
		hull.push_back(p[i]);
	}
	hull.pop_back();
}
//---codebook end

int n;
poi P[MAXN];
int main()
{
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		int cnt=0;
		for(int i=0; i<n; i++) {
			char yn[3];
			scanf("%lld %lld", &P[i].x, &P[i].y);
			scanf("%s", yn);
			if(yn[0] == 'Y')cnt++;
		}
		vector<poi> hull;
		ConvexHull(P, n, hull);
		//assert(cnt == hull.size());
		printf("%d\n", (int)hull.size());
		for(int i=0; i<(int)hull.size(); i++) {
			printf("%lld %lld\n", hull[i].x, hull[i].y);
		}
	}
	return 0;
}

