#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include <vector>

using namespace std;

#define MAXN 100005
#define ll long long int

struct poi {
        ll x, y;
        bool operator <(const poi &rhs)const {
                return x == rhs.x ? (y < rhs.y) : (x < rhs.x);
        }
}P[MAXN];

int n;

vector<int> hull;

int test(int i, int j, int k) {
        ll dx1 = P[j].x - P[i].x, dy1 = P[j].y - P[i].y;
        ll dx2 = P[k].x - P[i].x, dy2 = P[k].y - P[i].y;
        return dx1*dy2 - dx2*dy1 >= 0;
}

int main()
{
	int T;
        scanf("%d", &T);
        while(T--){
                hull.clear();
                scanf("%d", &n);
                int cnt=0;
                for(int i=0; i<n; i++) {
                        char yn[3];
                        scanf("%lld %lld", &P[i].x, &P[i].y);
                        scanf("%s", yn);
                        if(yn[0] == 'Y')cnt++;
                }
                sort(P, P+n);
                // upper
                hull.push_back(0);
                for(int i=1; i<n; i++) {
                        while(hull.size() > 1 && !test(hull[hull.size()-2], hull[hull.size()-1], i)) hull.pop_back();
                        hull.push_back(i);
                }
                unsigned int h1 = hull.size();
                // lower
                for(int i=n-2; i>0; i--) {
                        while(hull.size() > h1 && !test(hull[hull.size()-2], hull[hull.size()-1], i)) hull.pop_back();
                        hull.push_back(i);
                }
                assert(cnt == hull.size());
                printf("%d\n", (int)hull.size());
                for(int i=0; i<(int)hull.size(); i++) {
                        printf("%lld %lld\n", P[hull[i]].x, P[hull[i]].y);
                }
        }
        return 0;
}

