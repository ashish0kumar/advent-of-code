#include <bits/stdc++.h>
using namespace std;

int main()
{
    vector<tuple<int, int, int, int>> robots;
    string line;
    while (getline(cin, line))
    {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        robots.emplace_back(px, py, vx, vy);
    }

    for (int t = 0; t < 10000; t++)
    {
        set<pair<int, int>> st1, st2;
        for (auto &[px, py, vx, vy] : robots)
        {
            int xf = (px + t * vx) % 101, yf = (py + t * vy) % 103;
            if (xf < 0)
                xf += 101;
            if (yf < 0)
                yf += 103;

            if (st1.count({xf, yf}))
                st2.insert({xf, yf});

            for (int i = -1; i <= 1; i++)
                for (int j = -1; j <= 1; j++)
                    st1.insert({xf + i, yf + j});
        }

        if (st2.size() > 256)
        {
            cout << t << endl;
            break;
        }
    }

    return 0;
}