#include <bits/stdc++.h>

using namespace std;

// 简单模拟，字符串反转

class Solution
{
    char output[10005];

public:
    string reverseWords(string s)
    {
        vector<string> vec;
        int sp = -1;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] != ' ')
            {
                if (sp < 0)
                    sp = i;
            }
            else
            {
                if (sp >= 0)
                {
                    vec.push_back(s.substr(sp, i - sp));
                    sp = -1;
                }
            }
        }
        if (sp >= 0)
        {
            vec.push_back(s.substr(sp, s.size() - sp));
        }
        int op = 0;
        for (int i = vec.size() - 1; i >= 0; i--)
        {
            for (int j = 0; j < vec[i].size(); j++)
            {
                output[op++] = vec[i][j];
            }
            if (i == 0)
                output[op] = 0;
            else
                output[op++] = ' ';
        }
        return string(output);
    }
};

int main()
{

    return 0;
}