#include <bits/stdc++.h>

using namespace std;

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        int ans = 0;
        stack<int> S;
        int before = 0;
        for (int i = 0; i < s.length(); i++)
        {
            char c = s[i];
            int ic = 0;
            if (c == ')')
                ic = 1;
            if (S.size() == 0)
            {
                if (ic == 0)
                {
                    S.push(2 + before);
                    before = 0;
                }
                else
                {
                    before = 0;
                }
            }
            else
            {
                if (ic == 0)
                {
                    S.push(2 + before);
                    before = 0;
                }
                else
                {
                    int t = S.top();
                    ans = max(ans, t + before);
                    before += t;
                    S.pop();
                    // if (S.size() > 0)
                    // {
                    //     S.pop();
                    //     S.push(2 + t);
                    // }
                }
            }
            // cout << i << " " << before << endl;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    string s = "()(())";
    string ss = "(()())";
    cout << sol.longestValidParentheses(s) << endl;
    cout << "-----------" << endl;
    cout << sol.longestValidParentheses(ss) << endl;
    return 0;
}