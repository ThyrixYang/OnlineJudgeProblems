#include <bits/stdc++.h>

using namespace std;

// 暴力模拟

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        map<int, vector<pair<int, int>>> M;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                int a = nums[i];
                int b = nums[j];
                if (M.find(a + b) == M.end())
                    M[a + b] = vector<pair<int, int>>();
                M[a + b].push_back(make_pair(i, j));
            }
        }
        set<vector<int>> output;
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                int a = nums[i];
                int b = nums[j];
                int c = target - a - b;
                for (pair<int, int> p : M[c])
                {
                    int d = p.first;
                    int e = p.second;
                    if (d <= j)
                        continue;
                    vector<int> res = {nums[i], nums[j], nums[d], nums[e]};
                    sort(res.begin(), res.end());
                    output.insert(res);
                }
            }
        }
        vector<vector<int>> ans;
        for (auto v : output)
            ans.push_back(v);
        return ans;
    }
};

int main()
{

    return 0;
}