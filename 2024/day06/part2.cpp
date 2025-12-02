#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    int H = 130;
    vector<string> grid(H);

    for (int i = 0; i < H; i++)
        cin >> grid[i];

    int W = grid[0].length();

    pair<int, int> startMe{-1, -1};
    int dir = 0;

    for (int row = 0; row < H; row++)
    {
        for (int col = 0; col < W; col++)
        {
            if (grid[row][col] == '^')
            {
                startMe = {row, col};
                grid[row][col] = '.';
            }
        }
    }

    auto solveCycle = [&]()
    {
        pair<int, int> me = startMe;
        int dir = 0;

        vector<bool> vis(H * W * 4);

        while (true)
        {
            int hash = (me.first * W + me.second) * 4 + dir;
            if (vis[hash])
                return true;

            vis[hash] = true;

            int r2 = me.first + dirs[dir].first;
            int c2 = me.second + dirs[dir].second;

            if (!(0 <= r2 && r2 < H && 0 <= c2 && c2 < W))
                return false;

            if (grid[r2][c2] == '.')
                me = {r2, c2};

            else
                dir = (dir + 1) % 4;
        }
    };

    int res = 0;
    for (int row = 0; row < H; row++)
    {
        for (int col = 0; col < W; col++)
        {
            if (grid[row][col] == '.' && startMe != make_pair(row, col))
            {
                grid[row][col] = '#';

                if (solveCycle())
                    res++;

                grid[row][col] = '.';
            }
        }
    }

    cout << res << endl;
}