#include <bits/stdc++.h>
using namespace std;

int reps = 75;

long long dfs(long long curr, int bLeft, vector<unordered_map<long, long>> &dp)
{
    if (bLeft == 0)
        return 1;

    if (dp[bLeft].count(curr) != 0)
        return dp[bLeft][curr];

    int newBLeft = bLeft - 1;

    if (curr == 0)
        return dp[bLeft][curr] = dfs(curr + 1, newBLeft, dp);

    else if (to_string(curr).size() % 2 == 0)
    {
        string currStr = to_string(curr);
        int len = currStr.size() / 2;

        long long left = stoll(currStr.substr(0, len));
        long long right = stoll(currStr.substr(len, len));

        return dp[bLeft][curr] = dfs(left, newBLeft, dp) + dfs(right, newBLeft, dp);
    }

    else
        return dp[bLeft][curr] = dfs(curr * 2024, newBLeft, dp);
}

int main()
{
    vector<long long> nums;
    long long num;
    while (cin >> num)
        nums.push_back(num);

    vector<unordered_map<long, long>> dp(reps + 1);
    vector<long long> temp;

    for (int i = 0; i < nums.size(); i++)
        dfs(nums[i], reps, dp);

    long long res = 0;
    for (long long &num : nums)
        res += dp[reps][num];

    cout << res << endl;
}