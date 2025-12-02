#include <bits/stdc++.h>
using namespace std;

bool find(vector<string> &grid, int r, int c, int n, int m)
{
    if (r - 1 < 0 || r + 1 >= n || c - 1 < 0 || c + 1 >= m)
        return false;

    string tlbr = {grid[r - 1][c - 1], grid[r][c], grid[r + 1][c + 1]};
    string trbl = {grid[r - 1][c + 1], grid[r][c], grid[r + 1][c - 1]};

    string mas = "MAS", sam = "SAM";

    return ((tlbr == mas || tlbr == sam) && (trbl == mas || trbl == sam));
}

int main()
{
    vector<string> grid;
    string line;

    while (cin >> line)
        grid.push_back(line);

    int n = grid.size();
    int m = grid[0].size();
    int cnt = 0;

    for (int i = 1; i < n - 1; i++)
    {
        for (int j = 1; j < m - 1; j++)
        {
            if (find(grid, i, j, n, m))
                cnt++;
        }
    }

    cout << cnt << endl;

    return 0;
}