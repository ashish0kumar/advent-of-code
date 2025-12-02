#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs{{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void dfs(int r, int c, long long &res, vector<vector<int>> &grid)
{
    int curr = grid[r][c];
    if (curr == 9)
    {
        grid[r][c] = 0;
        res++;
        return;
    }

    for (auto &dir : dirs)
    {
        int nr = r + dir.first;
        int nc = c + dir.second;

        if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid[0].size() && grid[nr][nc] != 0)
        {
            int next = grid[nr][nc];
            if (curr + 1 == next)
                dfs(nr, nc, res, grid);
        }
    }

    return;
}

int main()
{
    vector<string> input;
    string line;

    while (cin >> line)
        input.push_back(line);

    vector<vector<int>> grid;
    vector<pair<int, int>> starts;

    for (int r = 0; r < input.size(); r++)
    {
        vector<int> temp(input[0].size());
        for (int c = 0; c < input[0].size(); c++)
        {
            int curr = input[r][c] - '0';
            temp[c] = curr;

            if (curr == 0)
                starts.push_back({r, c});
        }
        grid.push_back(temp);
    }

    long long res = 0;
    for (auto &start : starts)
    {
        vector<vector<int>> dup = grid;
        dfs(start.first, start.second, res, dup);
    }

    cout << res << endl;
}