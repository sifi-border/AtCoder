#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

template <int p>
struct Modint
{
    int value;

    Modint() : value(0) {}
    Modint(long long x) : value(x >= 0 ? x % p : (p + x % p) % p) {}

    inline Modint &operator+=(const Modint &b)
    {
        if ((this->value += b.value) >= p)
            this->value -= p;
        return (*this);
    }
    inline Modint &operator-=(const Modint &b)
    {
        if ((this->value += p - b.value) >= p)
            this->value -= p;
        return (*this);
    }
    inline Modint &operator*=(const Modint &b)
    {
        this->value = (int)((1LL * this->value * b.value) % p);
        return (*this);
    }
    inline Modint &operator/=(const Modint &b)
    {
        (*this) *= b.inverse();
        return (*this);
    }

    Modint operator+(const Modint &b) const { return Modint(*this) += b; }
    Modint operator-(const Modint &b) const { return Modint(*this) -= b; }
    Modint operator*(const Modint &b) const { return Modint(*this) *= b; }
    Modint operator/(const Modint &b) const { return Modint(*this) /= b; }

    inline Modint &operator++(int) { return (*this) += 1; }
    inline Modint &operator--(int) { return (*this) -= 1; }

    inline bool operator==(const Modint &b) const
    {
        return this->value == b.value;
    }
    inline bool operator!=(const Modint &b) const
    {
        return this->value != b.value;
    }
    inline bool operator<(const Modint &b) const
    {
        return this->value < b.value;
    }
    inline bool operator<=(const Modint &b) const
    {
        return this->value <= b.value;
    }
    inline bool operator>(const Modint &b) const
    {
        return this->value > b.value;
    }
    inline bool operator>=(const Modint &b) const
    {
        return this->value >= b.value;
    }

    // requires that "this->value and p are co-prime"
    // a_i * v + a_(i+1) * p = r_i
    // r_i = r_(i+1) * q_(i+1) * r_(i+2)
    // q == 1 (i > 1)
    // reference: https://atcoder.jp/contests/agc026/submissions/2845729
    // (line:93)
    inline Modint inverse() const
    {
        assert(this->value != 0);
        int r0 = p, r1 = this->value, a0 = 0, a1 = 1;
        while (r1)
        {
            int q = r0 / r1;
            r0 -= q * r1;
            swap(r0, r1);
            a0 -= q * a1;
            swap(a0, a1);
        }
        return Modint(a0);
    }

    friend istream &operator>>(istream &is, Modint<p> &a)
    {
        long long t;
        is >> t;
        a = Modint<p>(t);
        return is;
    }
    friend ostream &operator<<(ostream &os, const Modint<p> &a)
    {
        return os << a.value;
    }
};

const int MOD = 1e9 + 7;

using Int = Modint<MOD>;

Int modpow(Int e, long x)
{
    Int res = 1;
    while (x > 0)
    {
        if (x & 1)
            res *= e;
        res *= res;
        x >>= 1;
    }
    return res;
}

class Comb
{
public:
    vector<Int> fact, finv;
    Comb(int n) : fact(n + 1), finv(n + 1)
    {
        fact[0] = Int(1);
        for (int i = 1; i <= n; i++)
        {
            fact[i] = fact[i - 1] * Int(i);
        }
        finv[n] = Int(fact[n]).inverse();
        for (int i = n - 1; i >= 0; i--)
        {
            finv[i] = finv[i + 1] * Int(i + 1);
        }
    }

    inline Int nCk(int n, int k)
    {
        if (k < 0 || n < k)
            return Int(0);
        return Int(fact[n] * finv[n - k] * finv[k]);
    }

    inline Int nPk(int n, int k)
    {
        if (k < 0 || n < k)
            return Int(0);
        return Int(fact[n] * finv[n - k]);
    }
};

/*
verified @ https://atcoder.jp/contests/abc021/submissions/7096121
*/

int main(void)
{
    int n, k;
    cin >> n >> k;
    Comb comb(200020);
    cout << comb.nCk(n + k - 1, k) << endl;
    return 0;
}