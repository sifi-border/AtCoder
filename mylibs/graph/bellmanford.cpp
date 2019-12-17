#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <bitset>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

#define Rep(b, e, i) for(int i = b; i <= e; i++)
#define rep(n, i) Rep(0, n-1, i)

typedef long long ll;
typedef pair<ll, ll> llP;
typedef pair<int, int> intP;
typedef std::priority_queue<int> IntPrioQueue; //Z->A
typedef std::priority_queue<int, std::vector<int>, std::greater<int> > IntReversePrioQueue; //A->Z

const double PI = 3.14159265358979323846;
const double EPS = 1e-12;
const ll INF = 1e15;
const int MOD = 1000000007;

const int MAX_V = 1024;
const int MAX_E = 2048;

struct edge {int from, to; ll cost;};

edge es[MAX_E];

ll dis[MAX_V];
int V, E;
//ゴールに続く負の閉路が存在すればtrueを返す
bool bellmanford(int s) {
	rep(V, v) dis[v] = INF;
	dis[s] = 0LL;
	rep(V, i) {
		rep(E, e) {
			edge ne = es[e];
			if (dis[ne.from] != INF && dis[ne.to] > dis[ne.from] + ne.cost) {
				dis[ne.to] = dis[ne.from] + ne.cost;
				if (i == V-1) return true;
			}
		}
	}
	return false;
}
//abc061d
void solve(void){
    cin >> V >> E;
    rep(E, e){
        int a, b;ll c;
        scanf("%d %d %lld\n", &a, &b, &c);
        a--; b--;
        es[e] = edge {a, b, -c};
    }
    if (bellmanford(0)) cout << "inf" << endl;
    else cout << -dis[V-1] << endl;
}

int main(void){
  solve();
  return 0;
}
