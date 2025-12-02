#include <bits/stdc++.h>
using namespace std;

const int MOD = 1 << 24;
void f(long long &x)
{
    x ^= x * 64;
    x %= MOD;
    x ^= x / 32;
    x %= MOD;
    x ^= x * 2048LL;
    x %= MOD;
}

map<vector<int>, int> m;

int main()
{
    long long x;

    while (cin >> x)
    {
        vector<int> v;
        int n = 2000;
        v.push_back(x % 10);
        set<vector<int>> s;

        for (int i = 1; i <= n; i++)
        {
            f(x);
            v.push_back(x % 10);

            if (i >= 4)
            {
                vector<int> d;
                for (int j = 0; j < 4; j++)
                {
                    d.push_back(v[i - 4 + 1 + j] - v[i - 4 + j]);
                }

                if (!s.count(d))
                {
                    s.insert(d);
                    m[d] += x % 10;
                }
            }
        }
    }

    int res = 0;
    for (auto p : m)
    {
        res = max(res, p.second);
    }

    cout << res << endl;
}