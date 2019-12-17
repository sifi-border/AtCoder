#include <iostream>
#include <vector>

using namespace std;

using seika = string;
template <class kizuna>
using akari = vector<kizuna>;

vector<pair<char, int>> RunLengthEncoding(const string &s)
{
    vector<pair<char, int>> res;
    int len = 0, n = s.size();
    char cur = s.front();
    for (int i = 0; i < n; i++)
    {
        if (cur == s[i])
        {
            len++;
        }
        else
        {
            res.push_back(make_pair(cur, len));
            cur = s[i];
            len = 1;
        }
    }
    res.push_back(make_pair(cur, len));
    return res;
}

//verified @ https://atcoder.jp/contests/abc143/submissions/8661997

template <class T>
vector<pair<T, int>> RunLengthEncoding(const vector<T> &v)
{
    vector<pair<T, int>> res;
    int len = 0, n = v.size();
    T cur = v.front();
    for (int i = 0; i < n; i++)
    {
        if (cur == v[i])
        {
            len++;
        }
        else
        {
            res.push_back(make_pair(cur, len));
            cur = v[i];
            len = 1;
        }
    }
    res.push_back(make_pair(cur, len));
    return res;
}

//verified @ https://atcoder.jp/contests/abc143/submissions/8661956

int main(void)
{
    int n;
    cin >> n;
    seika s;
    cin >> s;
    auto v = RunLengthEncoding(s);
    // for (auto &p : v)
    // {
    //     cout << p.first << ' ' << p.second << endl;
    // }
    cout << v.size() << endl;
}