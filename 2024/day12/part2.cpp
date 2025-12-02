#include <bits/stdc++.h>
using namespace std;

vector<string> s;
vector<vector<bool>> vis;
int H, W;

const vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

bool inBounds(int row, int col)
{
    return row >= 0 && row < H && col >= 0 && col < W;
}

void dfs(int row, int col, int &area, int &per)
{
    vis[row][col] = true;
    area++;

    auto good = [&](pair<int, int> dir)
    {
        int nr = row + dir.first;
        int nc = col + dir.second;
        return inBounds(nr, nc) && s[row][col] == s[nr][nc];
    };

    for (int i = 0; i < 4; i++)
    {
        pair<int, int> dir1 = dirs[i];
        pair<int, int> dir2 = dirs[(i + 1) % 4];

        if (!good(dir1) && !good(dir2))
            per++;

        if (good(dir1) && good(dir2) && 
            !good(make_pair(dir1.first + dir2.first, dir1.second + dir2.second)))
            per++;
    }

    for (pair<int, int> dir : dirs)
    {
        int nr = row + dir.first;
        int nc = col + dir.second;
        if (good(dir) && !vis[nr][nc])
            dfs(nr, nc, area, per);
    }
}

int main()
{
    string line;
    while (cin >> line)
        s.push_back(line);

    H = s.size();
    W = s[0].size();
    vis.assign(H, vector<bool>(W, false));

    long long res = 0;
    for (int row = 0; row < H; row++)
    {
        for (int col = 0; col < W; col++)
        {
            if (!vis[row][col])
            {
                int area = 0, per = 0;
                dfs(row, col, area, per);
                res += area * per;
            }
        }
    }

    cout << res << endl;

    return 0;
}