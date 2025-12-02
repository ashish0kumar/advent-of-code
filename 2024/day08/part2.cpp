#include <bits/stdc++.h>
using namespace std;

bool inBounds(int r, int c, int rows, int cols)
{
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

int gcd(int a, int b)
{
    return b == 0 ? abs(a) : gcd(b, a % b);
}

int main()
{
    vector<string> input;
    string line;
    while (getline(cin, line))
        input.push_back(line);

    unordered_map<char, vector<pair<int, int>>> mp;
    int rows = input.size();
    int cols = input[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char curr = input[i][j];
            if (curr != '.')
                mp[curr].push_back({i, j});
        }
    }

    set<pair<int, int>> st;
    for (auto &it : mp)
    {
        const auto &pos = it.second;

        if (pos.size() > 1)
        {
            for (const auto &pos : pos)
                st.insert(pos);
        }

        for (int i = 0; i < pos.size(); i++)
        {
            for (int j = i + 1; j < pos.size(); j++)
            {
                auto [r1, c1] = pos[i];
                auto [r2, c2] = pos[j];

                int dr = r2 - r1;
                int dc = c2 - c1;

                int g = gcd(dr, dc);
                dr /= g;
                dc /= g;

                int k = -1;
                while (true)
                {
                    int nr = r1 + k * dr;
                    int nc = c1 + k * dc;

                    if (!inBounds(nr, nc, rows, cols))
                        break;

                    st.insert({nr, nc});
                    k--;
                }

                k = 1;
                while (true)
                {
                    int nr = r2 + k * dr;
                    int nc = c2 + k * dc;

                    if (!inBounds(nr, nc, rows, cols))
                        break;

                    st.insert({nr, nc});
                    k++;
                }
            }
        }
    }

    cout << st.size() << endl;
}