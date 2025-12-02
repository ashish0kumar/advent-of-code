#include <bits/stdc++.h>
using namespace std;

bool inBounds(int r, int c, int rows, int cols)
{
    return r >= 0 && r < rows && c >= 0 && c < cols;
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
        const auto &positions = it.second;
        for (int i = 0; i < positions.size(); i++)
        {
            for (int j = 0; j < positions.size(); j++)
            {
                if (i == j)
                    continue;

                auto [r1, c1] = positions[i];
                auto [r2, c2] = positions[j];

                int nr1 = r1 + (r1 - r2);
                int nc1 = c1 + (c1 - c2);

                int nr2 = r2 - (r1 - r2);
                int nc2 = c2 - (c1 - c2);

                if (inBounds(nr1, nc1, rows, cols))
                    st.insert({nr1, nc1});
                if (inBounds(nr2, nc2, rows, cols))
                    st.insert({nr2, nc2});
            }
        }
    }

    cout << st.size() << endl;
}