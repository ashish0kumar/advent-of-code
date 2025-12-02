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

vector<int> myOut;
void out(int x)
{
    myOut.push_back(combo(x) % 8);
    // cout << combo(x) % 8 << ",";
}

void bdv(int x)
{
    B = A >> combo(x);
}

void cdv(int x)
{
    C = A >> combo(x);
}

vector<pair<int, int>> v;

vector<int> simulate(long long _A)
{
    A = _A;
    i = 0;
    myOut.clear();
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
    return myOut;
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

    int x, y;
    while (scanf(" %d,%d", &x, &y) != EOF)
    {
        scanf(",");
        v.emplace_back(x, y);
    }

    // for (int ob : simulate(37221334433268LL))
    // {
    //     printf("%d,", ob);
    // }
    // puts("");
    // return 0;

    vector<int> targets;
    for (pair<int, int> p : v)
    {
        targets.push_back(p.first);
        targets.push_back(p.second);
    }

    vector<long long> cands;
    for (int i = 0; i < 1024; i++)
    {
        cands.push_back(i);
    }

    long long pw = 1024;
    vector<long long> firsts;
    for (int k = 0; k < (int)targets.size(); k++)
    {
        vector<long long> newCands;
        for (long long _A : cands)
        {
            vector<int> out = simulate(_A);
            bool ok = true;
            for (int j = 0; j <= k; j++)
            {
                if (j >= (int)out.size() || out[j] != targets[j])
                {
                    ok = false;
                    break;
                }
            }

            if (ok)
            {
                for (int j = 0; j < 8; j++)
                {
                    newCands.push_back(_A + j * pw);
                }
            }
        }
        cands = newCands;
        pw *= 8;

        sort(cands.begin(), cands.end());
        // printf("%d %lld %lld\n", (int)cands.size(), cands[0], cands.back());
        
        firsts.push_back(cands[0]);
    }

    cout << firsts.back() << endl;
}