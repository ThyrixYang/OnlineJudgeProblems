#include <bits/stdc++.h>

using namespace std;

class Solution
{
    int range_min[1005];
    int rm_front, rm_back;

public:
    int maxProfit(int k, vector<int> &prices)
    {
        memset(range_min, 0, sizeof(range_min));
        rm_front = rm_back = 0;
        int ans = 0;
        range_min[rm_back++] = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            for (int j = 1; j <= k; j++)
            {
            }
        }
    }
};

int main()
{

    return 0;
}