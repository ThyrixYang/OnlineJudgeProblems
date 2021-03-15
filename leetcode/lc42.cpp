#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int trap(vector<int> &height)
    {
        vector<int> forward(height.size() + 10, 0);
        vector<int> backward(height.size() + 10, 0);
        for (int i = 1; i <= height.size(); i++)
        {
            forward[i] = max(height[i - 1], forward[i - 1]);
        }
        for (int i = height.size(); i >= 1; i--)
        {
            backward[i] = max(backward[i + 1], height[i - 1]);
        }
        int ans = 0;
        for (int i = 1; i <= height.size(); i++)
        {
            int inc = min(forward[i - 1], backward[i + 1]);
            inc = max(0, inc - height[i - 1]);
            ans += inc;
        }
        return ans;
    }
};

int main()
{

    return 0;
}