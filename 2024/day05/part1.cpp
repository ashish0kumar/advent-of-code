#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    unordered_map<int, vector<int>> edges;
    long long res = 0;

    while (getline(cin, s))
    {
        if (s.empty() || !isdigit(s[0]))
            continue;

        int len = (int)s.length();
        vector<int> v;
        bool isPipe = false;
        
        for (int i = 0; i < len; i++)
        {
            if (isdigit(s[i]))
            {
                int num = 0;
                while (isdigit(s[i]))
                {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                v.push_back(num);
                if (s[i] == '|')
                    isPipe = true;

                assert(s[i] == ',' || s[i] == '|' || s[i] == '\n' || s[i] == 0);
            }
        }

        if (isPipe)
            edges[v[0]].push_back(v[1]);

        else
        {
            set<int> st;
            bool ok = true;
            for (int i = 0; i < v.size(); i++)
            {
                int u = v[i];
                for (int e : edges[u])
                {
                    if (st.count(e))
                        ok = false;
                }
                st.insert(u);
            }

            if (ok)
                res += v[v.size() / 2];
        }
    }

    cout << res << endl;
}