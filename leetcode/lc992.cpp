#include <bits/stdc++.h>

using namespace std;

// 双指针

class Solution
{
public:
    int subarraysWithKDistinct(vector<int> &A, int K)
    {
        vector<int> cnt_min(A.size() + 5, 0);
        vector<int> cnt_max(A.size() + 5, 0);
        int c_min = 0, c_max = 0;
        int f_min = 0, f_max = 0;
        int ans = 0;
        for (int i = 0; i < A.size(); i++)
        {
            int v = A[i];
            if (cnt_min[v] == 0)
            {
                c_min++;
            }
            cnt_min[v]++;
            if (cnt_max[v] == 0)
            {
                c_max++;
            }
            cnt_max[v]++;
            while (c_max > K)
            {
                cnt_max[A[f_max]]--;
                if (cnt_max[A[f_max]] == 0)
                    c_max--;
                f_max++;
            }
            while (c_min > K)
            {
                cnt_min[A[f_min]]--;
                if (cnt_min[A[f_min]] == 0)
                    c_min--;
                f_min++;
            }
            while (c_max == K && cnt_max[A[f_max]] > 1)
            {
                cnt_max[A[f_max]]--;
                f_max++;
            }
            if (c_max == c_min && c_max == K)
            {
                ans += f_max - f_min + 1;
            }
        }
        return ans;
    }
};

int main()
{

    return 0;
}