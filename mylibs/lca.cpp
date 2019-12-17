#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class LowestCommonAncestor
{
    //2^k >= n
    int n, k;
    vector<vector<int>> g, par;
    vector<int> dis;

    inline void build()
    {
        for (int i = 0; i < n; i++)
        {
            if (dis[i] == -1)
            {
                dis[i] = 0;
                this->calc(i);
            }
        }
        this->setpar();
    }

    void calc(int v = 0, int p = -1)
    {
        this->par[0][v] = p;
        for (int nv : this->g[v])
        {
            if (nv != p)
            {
                this->dis[nv] = this->dis[v] + 1;
                this->calc(nv, v);
            }
        }
    }

    void setpar()
    {
        for (int i = 0; i < this->k; i++)
        {
            for (int v = 0; v < this->n; v++)
            {
                if (this->par[i][v] != -1)
                {
                    this->par[i + 1][v] = this->par[i][par[i][v]];
                }
            }
        }
    }

public:
    LowestCommonAncestor(int n_, vector<vector<int>> &g_) : n(n_), g(g_), dis(n, -1)
    {
        k = log2(n + 1);
        this->par.assign(k + 1, vector<int>(n, -1));
        this->build();
    }

    int get(int u, int v)
    {
        //dis[u] <= dis[v]
        if (this->dis[u] > this->dis[v])
        {
            swap(u, v);
        }
        int d = this->dis[v] - this->dis[u];
        for (int i = k; i >= 0; i--)
        {
            if (d >> i & 1)
            {
                v = this->par[i][v];
            }
        }
        if (u == v)
        {
            return v;
        }
        for (int i = k; i >= 0; i--)
        {
            if (this->par[i][u] != this->par[i][v])
            {
                u = this->par[i][u];
                v = this->par[i][v];
            }
        }
        return this->par[0][v];
    }

    inline int dist(int u, int v)
    {
        return this->dis[u] + this->dis[v] - 2 * dis[this->get(u, v)];
    }
};

//verified @ https://onlinejudge.u-aizu.ac.jp/status/users/sifi_border/submissions/1/GRL_5_C/judge/3883181/C++14
//verified @ https://atcoder.jp/contests/abc014/submissions/7617701

int main(void)
{
    int n;
    vector<vector<int>> g;
    cin >> n;
    g.resize(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    LowestCommonAncestor lca(n, g);
    int q;
    cin >> q;
    while (q--)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        cout << lca.dist(u, v) + 1 << '\n';
    }
}