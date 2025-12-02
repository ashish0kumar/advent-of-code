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

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    int res = 0;
    for (int i = 0; i < v1.size(); i++)
        res += abs(v1[i] - v2[i]);

    cout << res << endl;

    return 0;
}