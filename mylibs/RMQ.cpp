#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

//一点更新区間min
template <class T>
class SegmentTree
{
private:
    int n;
    const T unit = (T)1e15;
    vector<T> node;

public:
    SegmentTree(int n_)
    {
        this->n = 1;
        while (this->n < n_)
        {
            this->n *= 2;
        }
        this->node.resize(2 * n - 1, this->unit);
    }

    SegmentTree(vector<T> v)
    {
        int n_ = v.size();
        this->n = 1;
        while (this->n < n_)
        {
            this->n *= 2;
        }
        node.resize(2 * this->n - 1, this->unit);
        for (int i = 0; i < this->n; i++)
        {
            this->node[this->n - 1 + i] = v[i];
        }
        for (int i = this->n - 2; i >= 0; i--)
        {
            this->node[i] = min(this->node[i * 2 + 1], this->node[i * 2 + 2]);
        }
    }

    void update(int idx, T val)
    {
        idx += this->n - 1;
        this->node[idx] = val;
        while (idx)
        {
            idx = (idx - 1) / 2;
            this->node[idx] = min(this->node[2 * idx + 1], this->node[2 * idx + 2]);
        }
    }

    T getmin(int a, int b, int now = 0, int l = 0, int r = -1)
    {
        if (r < 0)
        {
            r = this->n;
        }
        if (r <= a || b <= l)
        {
            return this->unit;
        }
        if (a <= l && r <= b)
        {
            return this->node[now];
        }
        T lVal = getmin(a, b, 2 * now + 1, l, (l + r) / 2);
        T rVal = getmin(a, b, 2 * now + 2, (l + r) / 2, r);
        return min(lVal, rVal);
    }
};

void solve()
{
    int n, q;
    cin >> n >> q;
    vector<long> v(n, (1LL << 31) - 1);
    SegmentTree<long> segtree(v);
    while (q--)
    {
        long c, x, y;
        cin >> c >> x >> y;
        if (c)
        {
            cout << segtree.getmin(x, y + 1) << '\n';
        }
        else
        {
            segtree.update(x, y);
        }
    }
}

int main()
{
    solve();
    return 0;
}
