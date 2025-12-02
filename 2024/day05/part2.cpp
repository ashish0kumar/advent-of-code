#include <bits/stdc++.h>
using namespace std;

unordered_map<int, vector<int>> edges;

void topo(int a, vector<int> &order, map<int, int> &in, const set<int> &present)
{
    order.push_back(a);
    for (int e : edges[a])
    {
        if (present.count(e) && --in[e] == 0)
            topo(e, order, in, present);
    }
}

int main()
{
    string s;
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

            map<int, int> in;
            set<int> present;

            for (int x : v)
                present.insert(x);

            for (int i = 0; i < (int)v.size(); i++)
            {
                int u = v[i];
                for (int e : edges[u])
                {
                    if (present.count(e))
                        ++in[e];
                    if (st.count(e))
                        ok = false;
                }
                st.insert(u);
            }

            if (!ok)
            {
                vector<int> order;
                vector<int> starting;

                for (int x : v)
                {
                    if (in[x] == 0)
                        starting.push_back(x);
                }

                for (int x : starting)
                    topo(x, order, in, present);

                res += order[order.size() / 2];
            }
        }
    }

    cout << res << endl;
}