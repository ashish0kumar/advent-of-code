#include <bits/stdc++.h>
using namespace std;

# define int long long

vector<vector<int>> numpad = {
    {7, 8, 9},
    {4, 5, 6},
    {1, 2, 3},
    {-1, 0, 10}}; // 10 = A

int getInt(char c)
{
    if (isdigit(c))
        return c - '0';
    if (c == 'A')
        return 10;
    assert(false);
}

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

const int INF = 1e18 + 5;
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

const int M = 25;
int dp[M + 2][11][11];

void preprocess()
{
    for (int id = 1; id <= M + 1; id++)
    {
        const int X = (id == M + 1 ? 11 : 5);
        for (int from = 0; from < X; from++)
        {
            vector<vector<int>> small(5, vector<int>(11, INF));
            small[HIT][from] = 0;
            set<pair<int, pair<int, int>>> pq;
            pq.insert({0, {HIT, from}});

            auto consider = [&](int prv, int me, int maybe)
            {
                if (maybe < small[prv][me])
                {
                    pq.erase({small[prv][me], {prv, me}});
                    small[prv][me] = maybe;
                    pq.insert({maybe, {prv, me}});
                }
            };

            while (!pq.empty())
            {
                int myDist = pq.begin()->first;
                int prv = pq.begin()->second.first;
                int me = pq.begin()->second.second;
                pq.erase(pq.begin());

                for (int prv2 = 0; prv2 < 5; prv2++)
                {
                    int maybe = myDist + dp[id - 1][prv][prv2];
                    consider(prv2, me, maybe);
                }
                if (prv != HIT)
                {
                    if (MOVEMENT == makeMove(prv, me, (id == M + 1 ? numpad : keypad)))
                    {
                        consider(prv, me, myDist + 1);
                    }
                }
            }

            for (int to = 0; to < (id == M + 1 ? 11 : 5); to++)
            {
                dp[id][from][to] = small[HIT][to];
            }
        }
    }
}

int solve(string s)
{
    char prv = 'A';
    int total = 0;
    for (char c : s)
    {
        total += dp[M + 1][getInt(prv)][getInt(c)] + 1;
        prv = c;
    }
    return total;
}

int32_t main()
{
    preprocess();
    int res = 0;
    for (int rep = 0; rep < 5; rep++)
    {
        string s;
        cin >> s;
        int x = solve(s);
        s.pop_back();
        res += x * stoi(s);
    }

    cout << res << endl;
}