#include <bits/stdc++.h>
using namespace std;

struct Robot
{
    int x, y, vx, vy;
};

int gcd(int a, int b)
{
    while (b != 0)
    {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

int main()
{
    int W = 101, H = 103, T = 100;
    vector<Robot> robots;

    string line;
    while (getline(cin, line))
    {
        int px, py, vx, vy;
        sscanf(line.c_str(), "p=%d,%d v=%d,%d", &px, &py, &vx, &vy);
        robots.push_back({px, py, vx, vy});
    }

    vector<vector<int>> v(2, vector<int>(2, 0));
    for (auto &r : robots)
    {
        int finalX = (r.x + r.vx * T) % W;
        int finalY = (r.y + r.vy * T) % H;
        if (finalX < 0)
            finalX += W;
        if (finalY < 0)
            finalY += H;

        if (finalX == W / 2 || finalY == H / 2)
            continue;

        int qx = (finalX < W / 2);
        int qy = (finalY < H / 2);
        v[qy][qx]++;
    }
    
    int res = v[0][0] * v[0][1] * v[1][0] * v[1][1];

    cout << res << endl;
    return 0;
}