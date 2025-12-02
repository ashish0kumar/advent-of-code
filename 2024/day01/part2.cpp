#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v1, v2;
    int n1, n2;

    while (cin >> n1 >> n2)
    {
        v1.push_back(n1);
        v2.push_back(n2);
    }

    unordered_map<int, int> mp;
    for (int i = 0; i < v2.size(); i++)
        mp[v2[i]]++;

    int res = 0;
    for (int i = 0; i < v1.size(); i++)
    {
        res += v1[i] * mp[v1[i]];
    }

    cout << res << endl;

    return 0;
}