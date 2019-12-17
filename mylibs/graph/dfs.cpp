//ATP001-a
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <functional>
using namespace std;

#define Rep(b, e, i) for(int i = b; i <= e; i++)
#define rep(n, i) Rep(0, n-1, i)
#define MAX 501
#define INF (ll)1e10
#define MOD 1000000007

typedef long long ll;
typedef pair<ll, ll> P;

int dx4[4]={1,0,-1,0};
int dy4[4]={0,1,0,-1};

ll R, C;
ll sx, sy;
ll gx, gy;
char map[MAX][MAX];
bool visited[MAX][MAX];

void dfs(){
    stack<P> Stack;
    //初期化
    rep(R, y) rep(C, x) visited[y][x] = false;

    Stack.push(P(sx, sy));
    while (Stack.size()) {
        P p = Stack.top(); Stack.pop();
        visited[p.second][p.first] = true;
        if (p.first == gx and p.second == gy) break;
        rep (4, i) {
            ll nx = p.first + dx4[i];
            ll ny = p.second + dy4[i];
            if (nx >= 0 && nx < C && ny >= 0 && ny < R){
                if (map[ny][nx] != '#' && !visited[ny][nx]) {
                    Stack.push(P(nx, ny));
                }
            }
        }
    }
}

void solve(void){
    cin >> R >> C;
    rep(R, i) scanf("%s\n", &map[i]);
    rep(R, y) rep(C, x) {
        if (map[y][x] == 's') {
            sx = x, sy = y;
        }
        if (map[y][x] == 'g') {
            gx = x, gy = y;
        }
    }
    dfs();
    /*
    cout << sx << ' ' << sy << endl;
    cout << gx << ' ' << gy << endl;
    rep(R, y) {
        rep(C, x) {
            cout << visited[y][x];
        }
        cout << endl;
    }
    */
    cout << (visited[gy][gx] ? "Yes" : "No") << endl;
}

int main(void){
  solve();
  return 0;
}
