#include <iostream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

bool isSafe(const vector<int> &v)
{
    bool inc = true, dec = true;

    for (int i = 1; i < v.size(); i++)
    {
        int d = v[i] - v[i - 1];
        if (abs(d) < 1 || abs(d) > 3)
            return false;

        if (d > 0)
            dec = false;
        else if (d < 0)
            inc = false;
    }

    return inc || dec;
}

int main()
{
    vector<vector<int>> r;
    string l;

    while (getline(cin, l))
    {
        stringstream ss(l);
        vector<int> t;
        int n;
        while (ss >> n)
            t.push_back(n);
        r.push_back(t);
    }

    int cnt = 0;
    for (const auto &t : r)
    {
        if (isSafe(t))
            cnt++;
    }

    cout << cnt << endl;

    return 0;
}