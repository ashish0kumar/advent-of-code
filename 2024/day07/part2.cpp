#include <bits/stdc++.h>
using namespace std;

int countDigs(long long num)
{
    int digits = 0;
    while (num > 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}

bool dfs(long long total, int i, long long goal, vector<long long> &nums)
{
    if (i == nums.size())
        return total == goal;

    long long curr = nums[i];

    return dfs(total + curr, i + 1, goal, nums) ||
           dfs(total * curr, i + 1, goal, nums) ||
           dfs(total * pow(10, countDigs(curr)) + curr, i + 1, goal, nums);
}

int main()
{
    long long res = 0;
    vector<string> input;
    string line;
    while (getline(cin, line))
        input.push_back(line);

    for (string &s : input)
    {
        int colonIdx = s.find(':');
        long long goal = stoll(s.substr(0, colonIdx));
        string rest = s.substr(colonIdx + 1);

        stringstream ss(rest);
        vector<long long> nums;
        long long n;
        while (ss >> n)
            nums.push_back(n);

        bool found = dfs(nums[0], 1, goal, nums);

        if (found)
            res += goal;
    }

    cout << res << endl;
    return 0;
}