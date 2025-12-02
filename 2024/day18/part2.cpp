#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 5;
const int S = 71;
bool vis[S][S];

int main()
{
    vector<pair<int, int>> in;
    const int N = 3450;
    vector<vector<int>> value(S, vector<int>(S, N + 1));
    vector<vector<int>> dist(S, vector<int>(S, 0));
    for (int i = 0; i < N; i++)
    {
        int x, y;
        scanf(" %d,%d", &x, &y);
        in.emplace_back(x, y);
        value[x][y] = i + 1;
    }

    vector<pair<int, int>> inv[N+3];
    dist[0][0] = value[0][0];
    inv[dist[0][0]].emplace_back(0, 0);

    for (int v = N + 1; v >= 0; v--) {
        for (int z = 0; z < (int)inv[v].size(); z++) {
            pair<int, int> me = inv[v][z];
            int r = me.first;
            int c = me.second;
            if (dist[r][c] != v) continue;

            for (pair<int, int> dir : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, 1}, {0, -1}})
            {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (0 <= min(nr, nc) && max(nr, nc) < S)
                {
                    int x = min(v, value[nr][nc]);
                    if (x > dist[nr][nc]) {
                        dist[nr][nc] = x;
                        inv[x].emplace_back(nr, nc);
                    }
                }
            }
        }
    }

    int id = dist[S - 1][S - 1] - 1;
    cout << in[id].first << "," << in[id].second << endl;
}