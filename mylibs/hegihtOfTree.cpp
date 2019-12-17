#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T = long>
vector<T> heightOfTree(const vector<vector<pair<int, T>>> &g)
{
    int n = g.size();
    auto dfs = [&](auto dfs, int v, vector<T> &dis) -> void {
        for (auto &p : g[v])
        {
            if (dis[p.first] == -1)
            {
                dis[p.first] = dis[v] + p.second;
                dfs(dfs, p.first, dis);
            }
        }
    };
    vector<T> dis(n, -1), dis2(dis);
    dis[0] = 0;
    dfs(dfs, 0, dis);
    int s1 = distance(dis.begin(), max_element(dis.begin(), dis.end()));
    fill(dis.begin(), dis.end(), -1);
    dis[s1] = 0;
    dfs(dfs, s1, dis);
    int s2 = distance(dis.begin(), max_element(dis.begin(), dis.end()));
    dis2[s2] = 0;
    dfs(dfs, s2, dis2);
    //cout << s1 << ' ' << s2 << endl;
    vector<T> res(n);
    for (int i = 0; i < n; i++)
    {
        //cout << dis[i] << ' ' << dis2[i] << endl;
        //cout << max(dis[i], dis2[i]) << '\n';
        res[i] = max(dis[i], dis2[i]);
    }
    return res;
}

//verified @ https://onlinejudge.u-aizu.ac.jp/problems/GRL_5_B

void solve()
{
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < n - 1; i++)
    {
        int s, t, w;
        cin >> s >> t >> w;
        g[s].push_back(make_pair(t, w));
        g[t].push_back(make_pair(s, w));
    }
    auto d = heightOfTree(g);
    for (int i = 0; i < n; i++)
    {
        cout << d[i] << '\n';
    }
}

int main()
{
    solve();
    return 0;
}
