#include <vector>

using namespace std;

using i64 = int_fast64_t;

vector<pair<i64, int>> factorize(i64 x)
{
    vector<pair<i64, int>> res;
    for (i64 f = 2; f * f <= x; f++)
    {
        if (x % f)
        {
            continue;
        }
        int cnt = 0;
        while (x % f == 0)
        {
            cnt++;
            x /= f;
        }
        res.push_back(make_pair(f, cnt));
    }
    if (x > 1)
    {
        res.push_back(make_pair(x, 1));
    }
    return res;
}