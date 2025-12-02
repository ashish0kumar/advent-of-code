#include <bits/stdc++.h>
using namespace std;

long long A, B, C;

long long combo(int x)
{
    if (x <= 3)
        return x;
    if (x == 4)
        return A;
    if (x == 5)
        return B;
    if (x == 6)
        return C;
    assert(false);
}

int i = 0;

void adv(int x)
{
    A >>= combo(x);
}

void bxl(int x)
{
    B ^= x;
}

void bst(int x)
{
    B = combo(x) % 8;
}

void jnz(int x)
{
    if (A == 0)
        return;
    i = x;
    i--;
}

void bxc(int x)
{
    B ^= C;
}

void out(int x)
{
    cout << combo(x) % 8 << ",";
}

void bdv(int x)
{
    B = A >> combo(x);
}

void cdv(int x)
{
    C = A >> combo(x);
}

int main()
{
    char s[105];
    scanf(" %s", s);
    scanf(" %s", s);
    scanf(" %lld", &A);

    for (int i = 0; i < 7; i++)
    {
        scanf(" %s", s);
    }

    vector<pair<int, int>> v;
    int x, y;
    while (scanf(" %d,%d", &x, &y) != EOF)
    {
        scanf(",");
        v.emplace_back(x, y);
    }

    while (0 <= i && i < (int)v.size())
    {
        int a = v[i].first;
        int x = v[i].second;

        switch (a)
        {
        case 0:
            adv(x);
            break;
        case 1:
            bxl(x);
            break;
        case 2:
            bst(x);
            break;
        case 3:
            jnz(x);
            break;
        case 4:
            bxc(x);
            break;
        case 5:
            out(x);
            break;
        case 6:
            bdv(x);
            break;
        case 7:
            cdv(x);
            break;
        }
        i++;
    }
    puts("");
}