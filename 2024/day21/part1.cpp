#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> numpad = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
    {-1, 0, 10}}; // 10 = A

char getChar(int value)
{
    if (0 <= value && value < 10)
        return '0' + value;

    if (value == 10)
        return 'A';

    return false;
}

const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, HIT = 4;
pair<int, int> dirs[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<vector<int>> keypad = {
    {-1, UP, HIT},
    {LEFT, DOWN, RIGHT}};

pair<int, int> f(pair<int, int> me, int dir)
{
    assert(0 <= dir && dir < 4);
    return {me.first + dirs[dir].first, me.second + dirs[dir].second};
}

const int INF = 1e9 + 5;
int dist[5][5][5][11];
bool vis[5][5][5][11];

const char MOVEMENT = '$';
const char ERROR = '@';

char makeMove(int mv, int &x, vector<vector<int>> pad)
{
    assert(0 <= mv && mv < 4);
    int H = pad.size();
    int W = pad[0].size();

    for (int r = 0; r < H; r++)
    {
        for (int c = 0; c < W; c++)
        {
            if (pad[r][c] == x)
            {
                r += dirs[mv].first;
                c += dirs[mv].second;

                if (0 <= r && r < H && 0 <= c && c < W && pad[r][c] != -1)
                {
                    x = pad[r][c];
                    return MOVEMENT;
                }
                else
                    return ERROR;
            }
        }
    }
    assert(false);
}

char apply(int mv, int i, vector<int> &v)
{
    assert((int)v.size() == 3);
    assert(0 <= i && i < 3);

    if (mv == HIT)
    {
        if (i == 2)
            return getChar(v[2]);

        return apply(v[i], i + 1, v);
    }
    return makeMove(mv, v[i], (i == 2 ? numpad : keypad));
}

int solve(string s)
{
    memset(vis, 0, sizeof(vis));
    memset(dist, 0, sizeof(dist));

    dist[0][HIT][HIT][10] = 0;
    vis[0][HIT][HIT][10] = true;
    vector<vector<int>> q;
    q.push_back({0, HIT, HIT, 10});

    for (int z = 0; z < (int)q.size(); z++)
    {
        int chars = q[z][0], r1 = q[z][1], r2 = q[z][2], r3 = q[z][3];
        if (chars == (int)s.length())
            return dist[chars][r1][r2][r3];

        for (int mv = 0; mv < 5; mv++)
        {
            vector<int> v = q[z];
            v.erase(v.begin());

            char pr = apply(mv, 0, v);
            if (pr == ERROR)
                continue;

            if (pr != MOVEMENT)
            {
                if (pr != s[chars])
                    continue;
            }

            int s1 = chars + (pr != MOVEMENT);
            int s2 = v[0];
            int s3 = v[1];
            int s4 = v[2];

            if (!vis[s1][s2][s3][s4])
            {
                vis[s1][s2][s3][s4] = true;
                dist[s1][s2][s3][s4] = dist[chars][r1][r2][r3] + 1;
                q.push_back({s1, s2, s3, s4});
            }
        }
    }
    assert(false);
}

int main()
{
    int res = 0;
    for (int rep = 0; rep < 5; rep++)
    {
        string s;
        cin >> s;
        // s = "029A";
        int x = solve(s);
        s.pop_back();
        res += x * stoi(s);
    }

    cout << res << endl;
}