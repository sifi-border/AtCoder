#include <iostream>
#include <vector>

using namespace std;

template <class T>
class WeightedUnionFind
{
    vector<int> par;
    vector<T> dist;

public:
    WeightedUnionFind(int n) : par(n, -1), dist(n, 0) {}

    int root(int x)
    {
        if (par[x] < 0)
            return x;
        else
        {
            //rootから降りて足していく
            int r = root(par[x]);
            //親までの累積和は計算し終わっている
            dist[x] += dist[par[x]];
            return par[x] = r;
        }
    }

    //d[y] = d[x] + w
    bool merge(int x, int y, T w)
    {
        //par[y] = x
        w += weight(x) - weight(y);
        x = root(x);
        y = root(y);
        if (x == y)
            return false;
        if (par[x] > par[y])
        {
            w = -w;
            swap(x, y);
        }
        par[x] += par[y];
        par[y] = x;
        dist[y] = w;
        return true;
    }

    T weight(int x)
    {
        root(x);
        return dist[x];
    }

    T dis(int x, int y) { return weight(y) - weight(x); }

    int size(int x) { return -par[root(x)]; }
};

//verified @ https://onlinejudge.u-aizu.ac.jp/solutions/problem/DSL_1_B/review/3922525/sifi_border/C++14

int main(void)
{
    int n, q, c;
    cin >> n >> q;
    WeightedUnionFind<long> wuf(n);
    while (q--)
    {
        cin >> c;
        if (c)
        {
            int x, y;
            cin >> x >> y;
            if (wuf.root(x) == wuf.root(y))
            {
                cout << wuf.dis(x, y) << '\n';
            }
            else
            {
                cout << "?\n";
            }
        }
        else
        {
            int x, y;
            long z;
            cin >> x >> y >> z;
            wuf.merge(x, y, z);
        }
    }
    return 0;
}