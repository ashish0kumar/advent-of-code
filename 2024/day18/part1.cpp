#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
const int S = 71;
bool vis[S][S];

int main()
{
    for (int i = 0; i < 1024; i++)
    {
        int x, y;
        scanf(" %d,%d", &x, &y);
        vis[x][y] = true;
    }

    assert(!vis[0][0]);
    vector<vector<int>> dist(S, vector<int>(S, INF));
    vector<pair<int, int>> q;
    q.emplace_back(0, 0);

    dist[0][0] = 0;
    vis[0][0] = true;

    for (int i = 0; i < (int)q.size(); i++)
    {
        int r = q[i].first;
        int c = q[i].second;
        for (pair<int, int> dir : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, 1}, {0, -1}})
        {
            int nr = r + dir.first;
            int nc = c + dir.second;

            if (0 <= min(nr, nc) && max(nr, nc) < S && !vis[nr][nc])
            {
                vis[nr][nc] = true;
                dist[nr][nc] = dist[r][c] + 1;
                q.emplace_back(nr, nc);
            }
        }
    }

    cout << dist[S - 1][S - 1] << endl;
}