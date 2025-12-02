#include <bits/stdc++.h>
using namespace std;

int getNum(const string &s, int &i)
{
    int n = s.length();
    int num = 0;
    while (i < n && num < 1000 && isdigit(s[i]))
    {
        num = num * 10 + (s[i] - '0');
        i++;
    }

    if (1 <= num && num <= 999)
        return num;
    return -1;
};

int main()
{
    string s;
    char c;

    while (cin.get(c))
        s += c;

    int n = (int)s.length();
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'm')
        {
            if (i + 3 < n && s[i + 1] == 'u' && s[i + 2] == 'l' && s[i + 3] == '(')
            {
                i += 4;
                int n1 = getNum(s, i);

                if (i < n && s[i] == ',')
                {
                    i += 1;
                    int n2 = getNum(s, i);

                    if (i < n && s[i] == ')')
                    {
                        if (n1 != -1 && n2 != -1)
                        {
                            res += n1 * n2;
                        }
                    }
                }
            }
        }
    }

    cout << res << endl;

    return 0;
}