#include <bits/stdc++.h>
using namespace std;

int main()
{
    string input;
    cin >> input;

    vector<int> nums;
    int id = 0;

    vector<pair<int, int>> free;
    vector<pair<int, int>> used;

    for (int i = 0; i < input.size(); i++)
    {
        int n = input[i] - '0';
        if (i == 0 || i % 2 == 0)
        {
            used.push_back({nums.size(), n});
            for (int j = 0; j < n; j++)
                nums.push_back(id);
            id++;
        }
        else
        {
            free.push_back({nums.size(), n});
            for (int j = 0; j < n; j++)
                nums.push_back(-1);
        }
    }

    int l = 0, r = nums.size() - 1;
    
    for (int i = used.size()-1; i >= 0; i--) {
        pair<int, int> curr = used[i];
        int usedS = curr.first;
        int usedL = curr.second;

        for (int freeIdx = 0; freeIdx < free.size(); freeIdx++) {
            pair<int, int> freeBlock = free[freeIdx];
            int freeS = freeBlock.first;
            int freeL = freeBlock.second;

            if (freeS + freeL > usedS) {
                break;
            }

            if (freeL >= usedL) {
                for (int j = freeS; j < freeS + usedL; j++) {
                    nums[j] = nums[usedS];
                }
                for (int j = usedS; j < usedS + usedL; j++) {
                    nums[j] = -1;
                }

                free = {};
                int x = 0;

                while (x < nums.size()) {
                    if (nums[x] == -1) {
                        int start = x;
                        int cnt = 0;

                        while (x < nums.size() && nums[x] == -1) {
                            cnt++;
                            x++;
                        }
                        free.push_back({start, cnt});
                    } else {
                        x++;
                    }
                }
                break;
            }
        }
    }

    long long res = 0;
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != -1) {
            res += i * nums[i];
        }
    }

    cout << res << endl;
}