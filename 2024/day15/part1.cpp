#include <bits/stdc++.h>
using namespace std;

char a[105][105];

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
    for (int row = 0; row < H; row++)
        for (int col = 0; col < W; col++)
            if (a[row][col] == '@')
            {
                me = {row, col};
                a[row][col] = '.';
            }
    assert(me.first != -1);

    for (char move : moves)
    {
        pair<int, int> dir = getDir(move);
        vector<pair<int, int>> boxes;
        int row = me.first;
        int col = me.second;
        bool emptySpace = false;

        while (true)
        {
            row += dir.first;
            col += dir.second;

            if (a[row][col] == '#')
                break;

            if (a[row][col] == '.')
            {
                emptySpace = true;
                break;
            }
            assert(a[row][col] == 'O');
            boxes.emplace_back(row, col);
        }

        if (!emptySpace)
            continue;

        me.first += dir.first;
        me.second += dir.second;

        for (pair<int, int> box : boxes)
            a[box.first][box.second] = '.';

        for (pair<int, int> box : boxes)
            a[box.first + dir.first][box.second + dir.second] = 'O';
    }

    int res = 0;
    for (int row = 0; row < H; row++)
        for (int col = 0; col < W; col++)
            if (a[row][col] == 'O')
                res += 100 * row + col;

    cout << res << endl;
}