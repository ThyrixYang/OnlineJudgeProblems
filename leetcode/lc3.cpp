#include <bits/stdc++.h>

using namespace std;

// 双指针

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        map<char, int> cnt;
        for (int i = 0; i < 250; i++)
        {
            cnt[char(i)] = 0;
        }
        int ans = 0;
        int f = 0;
        for (int i = 0; i < s.length(); i++)
        {
            cnt[s[i]]++;
            if (cnt[s[i]] > 1)
            {
                while (s[f] != s[i])
                    cnt[s[f]]--, f++;
                cnt[s[f]]--, f++;
            }
            ans = max(ans, i + 1 - f);
        }
        return ans;
    }
};

int main()
{

    return 0;
}