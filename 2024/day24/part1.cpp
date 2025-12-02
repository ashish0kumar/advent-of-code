#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<string, int> value;
    for (int i = 0; i < 90; i++)
    {
        char s[7];
        cin >> s;
        int d;
        cin >> d;
        value[string(s, s + 3)] = d;
    }

    char a[5], op[5], b[5], c[5];
    vector<vector<string>> ops;

    while (cin >> a)
    {
        scanf(" %s %s -> %s", op, b, c);
        vector<string> v{string(a), string(b), string(c), string(op)};
        ops.push_back(v);
    }

    for (int rep = 0; rep < (int)ops.size(); rep++)
    {
        for (vector<string> op : ops)
        {
            if (value.count(op[0]) && value.count(op[1]) && !value.count(op[2])) {
                int x = value[op[0]];
                int y = value[op[1]];
                string o = op[3];
                value[op[2]] = (o == "XOR" ? x^y : (o == "OR" ? x|y : x&y));
            }
        }
    }

    long long res = 0;
    int i = 0;

    for (auto p : value) {
        if (p.first[0] == 'z') {
            res += ((long long)p.second << i);
            i++;
        }
    }

    cout << res << endl;
}