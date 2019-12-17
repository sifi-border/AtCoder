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
#define Repr(e, b, i) for(int i = e; i >= b; i--)
#define rep(n, i) Rep(0, n-1, i)
#define repr(n, i) Repr(n-1, 0, i)
#define all(v) (v).begin(), (v).end()
#define pb(v) push_back(v)
#define uniq(v) (v).erase(unique(all(v)),(v).end())
#define bitcnt(x) __builtin_popcount(x)


/////////////////////////

const int MAX_V = 20000;
const int INF_F = 1<<29;

struct Edge {int to, cap, rev;};

struct Dinic {
	vector <Edge> G[MAX_V];
	int level[MAX_V], iter[MAX_V];

	void add_edge(int from, int to, int cap) {
		Edge e1 = {to, cap, (int)G[to].size()}, e2 = {from, 0, (int)G[from].size()-1};
		G[from].pb(e1), G[to].pb(e2);
	}

	void bfs(int s) {
		memset(level, -1, sizeof(level));
		queue <int> q;
		level[s] = 0;
		q.push(s);
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			for (auto &e : G[v]) {
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					q.push(e.to);
				}
			}
		}
	}

	int dfs(int v, int t, int f) {
		if (v == t) return f;
		for (int &i = iter[v]; i < (int)G[v].size(); i++) {
			Edge &e = G[v][i];
			if (e.cap > 0 && level[v] < level[e.to]) {
				int d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

	int max_flow(int s, int t) {
		int flow = 0;
		while (1) {
			bfs(s);
			if (level[t] < 0) return flow;
			memset(iter, 0, sizeof(iter));
			int f;
			while ((f = dfs(s, t, INF_F)) > 0) {
				flow += f;
			}
		}
	}

};
///////////////////////

//マークしてる女の子のid
vector <int> ps;

void solve(void){
    int N, G, E;
    cin >> N >> G >> E;
    ps.resize(G);
    rep(G, i) cin >> ps[i];

    Dinic dinic;

    rep(E, meaningless_) {
        int a, b;
        cin >> a >> b;
        dinic.add_edge(a, b, 1);
        dinic.add_edge(b, a, 1);
    }

    for (int p : ps) {
        dinic.add_edge(p, N, 1);
    }

    cout << dinic.max_flow(0, N) << endl;

}

int main(void){
  solve();
  //cout << "yui(*-v・)yui" << endl;
  return 0;
}
