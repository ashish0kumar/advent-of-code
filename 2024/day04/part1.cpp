#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs = {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

bool find(vector<string> &grid, int r, int c, int n, int m, int dir, string &target)
{
    int dr = dirs[dir].first;
    int dc = dirs[dir].second;

    for (int i = 0; i < 4; i++)
    {
        int nr = r + i * dr;
        int nc = c + i * dc;

        if (nr < 0 || nr >= n || nc < 0 || nc >= m || grid[nr][nc] != target[i])
            return false;
    }

    return true;
}

int main()
{
    vector<string> grid;
    string line;
    string target = "XMAS";

    while (cin >> line)
        grid.push_back(line);

    int n = grid.size();
    int m = grid[0].size();
    int cnt = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int d = 0; d < 8; d++)
            {
                if (find(grid, i, j, n, m, d, target))
                    cnt++;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}