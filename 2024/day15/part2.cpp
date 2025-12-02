#include <bits/stdc++.h>
using namespace std;

char a[105][105];
int id[105][105], tmp[105][105];

pair<int, int> getDir(char c)
{
    if (c == '^')
        return {-1, 0};
    if (c == 'v')
        return {1, 0};
    if (c == '>')
        return {0, 1};
    if (c == '<')
        return {0, -1};
    assert(false);
}

int main()
{
    int H, W;
    string moves;
    for (int row = 0; true; row++)
    {
        cin >> a[row];
        W = strlen(a[row]);
        if (W == 0 || W == 1 || (row >= 1 && W != (int)strlen(a[row - 1])))
        {
            H = row;
            W = strlen(a[row - 1]);
            moves += string(a[row]);
            while (cin >> a[row])
                moves += string(a[row]);
            break;
        }
    }

    pair<int, int> me{-1, -1};
    int nextId = 1;
    for (int row = 0; row < H; row++)
    {
        for (int col = 0; col < W; col++)
        {
            if (a[row][col] == '@')
            {
                me = {row, col};
                a[row][col] = '.';
            }
        }
        for (int col = 2 * W - 1; col >= 0; col--)
        {
            a[row][col] = a[row][col / 2];
            if (a[row][col / 2] == 'O')
            {
                id[row][col] = nextId;
                if (col % 2 == 0)
                    nextId++;
            }
        }
    }

    W *= 2;
    me.second *= 2;

    assert(me.first != -1);

    for (char move : moves)
    {
        pair<int, int> dir = getDir(move);
        vector<pair<int, int>> boxes;
        set<int> vis;
        boxes.push_back(me);
        bool anyBlocked = false;

        for (int i = 0; i < (int)boxes.size(); i++)
        {
            int row = boxes[i].first + dir.first;
            int col = boxes[i].second + dir.second;

            if (a[row][col] == '#')
            {
                anyBlocked = true;
                break;
            }

            if (a[row][col] == 'O')
            {
                if (!vis.count(id[row][col]))
                {
                    vis.insert(id[row][col]);
                    boxes.emplace_back(row, col);
                    for (int c : {col - 1, col + 1})
                    {
                        if (id[row][col] == id[row][c])
                            boxes.emplace_back(row, c);
                    }
                }
            }
        }

        if (anyBlocked)
            continue;

        me.first += dir.first;
        me.second += dir.second;

        boxes.erase(boxes.begin());

        for (pair<int, int> box : boxes)
        {
            a[box.first][box.second] = '.';
            tmp[box.first][box.second] = id[box.first][box.second];
            id[box.first][box.second] = 0;
        }

        for (pair<int, int> box : boxes)
        {
            id[box.first + dir.first][box.second + dir.second] = tmp[box.first][box.second];
            a[box.first + dir.first][box.second + dir.second] = 'O';
        }
    }

    int res = 0;
    for (int row = 0; row < H; row++)
        for (int col = 0; col < W; col++)
            if (a[row][col] == 'O' && id[row][col] != id[row][col - 1])
                res += 100 * row + col;

    cout << res << endl;
}