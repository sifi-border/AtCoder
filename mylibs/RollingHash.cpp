#include <iostream>
#include <vector>
#include <set>

using namespace std;

class RollingHash
{
    /*
        Reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
    */
public:
    //must be 64bit
    using yuzuki = uint_fast64_t;

    static const yuzuki base = 10009;
    static const yuzuki mod = (1ULL << 61) - 1;
    static const yuzuki MASK30 = (1ULL << 30) - 1;
    static const yuzuki MASK31 = (1ULL << 31) - 1;
    static const yuzuki SUP = mod * 3ULL;

    vector<yuzuki> hashed, powmemo;

    inline yuzuki mul(yuzuki a, yuzuki b) const
    {
        yuzuki au = a >> 31;
        yuzuki ad = a & MASK31;
        yuzuki bu = b >> 31;
        yuzuki bd = b & MASK31;
        yuzuki mid = ad * bu + au * bd;
        yuzuki midu = mid >> 30;
        yuzuki midd = mid & MASK30;
        return applyMod(au * bu * 2 + midu + (midd << 31) + ad * bd);
    }

    inline yuzuki applyMod(yuzuki val) const
    {
        val = (val & mod) + (val >> 61);
        if (val > mod)
        {
            val -= mod;
        }
        return val;
    }

    RollingHash(const string &s)
    {
        int n = (int)s.size();
        hashed.resize(n + 1);
        powmemo.resize(n + 1);
        powmemo[0] = 1;
        for (int i = 0; i < n; ++i)
        {
            hashed[i + 1] = applyMod(mul(hashed[i], base) + s[i]);
            powmemo[i + 1] = applyMod(mul(powmemo[i], base));
        }
    }

    template <typename T>
    RollingHash(const vector<T> &s)
    {
        int n = (int)s.size();
        hashed.resize(n + 1);
        powmemo.resize(n + 1);
        powmemo[0] = 1;
        for (int i = 0; i < n; ++i)
        {
            hashed[i + 1] = applyMod(mul(hashed[i], base) + s[i]);
            powmemo[i + 1] = applyMod(mul(powmemo[i], base));
        }
    }

    //[l, r)
    inline yuzuki get(int l, int r) const
    {
        if (l >= r)
        {
            return 0ULL;
        }
        return applyMod(hashed[r] + SUP - mul(hashed[l], powmemo[r - l]));
    }

    inline yuzuki connect(const yuzuki &h1, const yuzuki &h2, int h2len) const
    {
        return applyMod(h2 + mul(h1, powmemo[h2len]));
    }

    inline int LCP(const RollingHash &b, int l1, int r1, int l2, int r2) const
    {
        int ok = 0, ng = min(r2 - l2, r1 - l1) + 1;
        while (ok + 1 < ng)
        {
            int m = (ok + ng) / 2;
            (get(l1, l1 + m) == b.get(l2, l2 + m) ? ok : ng) = m;
        }
        return ok;
    }
};

//verified @ https://onlinejudge.u-aizu.ac.jp/status/users/sifi_border/submissions/1/2444/judge/4052863/C++14

//https://onlinejudge.u-aizu.ac.jp/status/users/sifi_border/submissions/1/ALDS1_14_B/judge/4051290/C++14
void solve_ALDS1_14_B(void)
{
    string s, t;
    cin >> s >> t;
    RollingHash rh1(s), rh2(t);
    int n = s.size(), m = t.size();
    for (int i = 0; i + m <= n; i++)
    {
        if (rh1.get(i, i + m) == rh2.get(0, m))
        {
            cout << i << '\n';
        }
    }
}

//http://codeforces.com/contest/514/submission/67000339
void solve_Watto_and_Mechanism(void)
{
    int n, m;
    cin >> n >> m;
    set<RollingHash::yuzuki> hashes;
    while (n--)
    {
        string s;
        cin >> s;
        RollingHash rh(s);
        hashes.insert(rh.get(0, s.size()));
    }
    RollingHash abc[] = {RollingHash("a"), RollingHash("b"), RollingHash("c")};
    while (m--)
    {
        string t;
        cin >> t;
        RollingHash rh(t);
        int L = t.size();
        bool found = 0;
        for (int i = 0; i < L; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (t[i] - 'a' == j)
                {
                    continue;
                }
                auto tmp = rh.connect(rh.get(0, i), abc[j].get(0, 1), 1);
                auto hashVal = rh.connect(tmp, rh.get(i + 1, L), L - i - 1);
                if (hashes.find(hashVal) != hashes.end())
                {
                    found = 1;
                }
            }
        }
        cout << (found ? "YES" : "NO") << '\n';
    }
}

//https://atcoder.jp/contests/abc141/submissions/8976092
void solve_Who_Says_a_Pun(void)
{
    int n;
    string s;
    cin >> n >> s;
    RollingHash rh(s);
    int ans = 0;
    for (int l1 = 0; l1 < n; l1++)
        for (int l2 = l1 + 1; l2 < n; l2++)
        {
            ans = max(ans, rh.LCP(rh, l1, l2, l2, n));
        }
    cout << ans << endl;
}

int main(void)
{
    //solve_ALDS1_14_B();
    //solve_Watto_and_Mechanism();
    //solve_Who_Says_a_Pun();
    return 0;
}