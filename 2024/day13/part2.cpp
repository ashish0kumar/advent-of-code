#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long ax, ay, bx, by, xres, yres;
    const long long offset = 10000000000000LL;
    long long res = 0;
    string line;

    while (getline(cin, line))
    {
        sscanf(line.c_str(), "Button A: X+%lld, Y+%lld", &ax, &ay);

        getline(cin, line);
        sscanf(line.c_str(), "Button B: X+%lld, Y+%lld", &bx, &by);

        getline(cin, line);
        sscanf(line.c_str(), "Prize: X=%lld, Y=%lld", &xres, &yres);

        getline(cin, line);

        xres += offset;
        yres += offset;

        long long bNume = (xres * ay - yres * ax);
        long long bDenom = (bx * ay - by * ax);

        if (bDenom == 0 || bNume % bDenom != 0)
            continue;

        long long b = bNume / bDenom;
        if (b < 0)
            continue;

        long long aNume = xres - b * bx;
        if (ax == 0 || aNume % ax != 0)
            continue;

        long long a = aNume / ax;
        if (a < 0)
            continue;

        res += a * 3 + b;
    }

    cout << res << endl;
}