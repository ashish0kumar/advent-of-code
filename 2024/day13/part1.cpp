#include <bits/stdc++.h>
using namespace std;

int main()
{
    int ax, ay, bx, by, xres, yres;
    int res = 0;
    string line;

    while (getline(cin, line))
    {
        sscanf(line.c_str(), "Button A: X+%d, Y+%d", &ax, &ay);

        getline(cin, line);
        sscanf(line.c_str(), "Button B: X+%d, Y+%d", &bx, &by);

        getline(cin, line);
        sscanf(line.c_str(), "Prize: X=%d, Y=%d", &xres, &yres);

        getline(cin, line);

        bool found = false;
        for (int i = 0; i < 100; i++)
        {
            for (int j = 0; j < 100; j++)
            {
                if (i * ax + j * bx == xres && i * ay + j * by == yres)
                {
                    res += i * 3 + j;
                    found = true;
                    break;
                }
            }
            if (found)
                break;
        }
    }

    cout << res << endl;
}