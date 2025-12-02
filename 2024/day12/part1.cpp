#include <bits/stdc++.h>
using namespace std;

vector<string> s;
vector<vector<bool>> vis;
int H, W;

const vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

bool inBounds(int row, int col)
{
    return row >= 0 && row < H && col >= 0 && col < W;
}

void dfs(int row, int col, int &area, int &per)
{
    vis[row][col] = true;
    area++;

    for (const auto &[dr, dc] : dirs)
    {
        int nr = row + dr;
        int nc = col + dc;

        if (!inBounds(nr, nc) || s[row][col] != s[nr][nc])
            per++;
        else if (!vis[nr][nc])
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