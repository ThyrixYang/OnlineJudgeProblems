
#include <bits/stdc++.h>

using namespace std;

// 简单模拟分支判断

class Solution
{
    bool onlyDigit(string s)
    {
        int cnt_d = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                return false;
            }
            else
            {
                cnt_d += 1;
            }
        }
        if (cnt_d == 0)
            return false;
        return true;
    }
    bool isInteger(string s)
    {
        if (s.length() == 0)
            return false;
        if (s[0] == '-' || s[0] == '+')
        {
            if (onlyDigit(s.substr(1)))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            if (onlyDigit(s))
                return true;
            else
            {
                return false;
            }
        }
    }

    bool _isNumber(string s)
    {
        int p = -1;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'e' || s[i] == 'E')
            {
                if (p != -1)
                {
                    return false;
                }
                p = i;
            }
        }
        if (p == -1)
            return false;
        string before = s.substr(0, p);
        if (!isDecimal(before) && !isInteger(before))
        {
            return false;
        }
        string after = s.substr(p + 1);
        if (!isInteger(after))
            return false;
        return true;
    }

    bool isDecimal(string s)
    {
        if (s[0] == '-' || s[0] == '+')
        {
            for (int i = 1; i < s.length(); i++)
            {
                if (s[i] == '-' || s[i] == '+')
                {
                    return false;
                }
            }
            s = s.substr(1);
        }
        int cnt_dot = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '.')
                cnt_dot++;
            if (cnt_dot >= 2)
                return false;
        }
        int cnt_d = 0;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] < '0' || s[i] > '9')
            {
                if (s[i] != '.')
                    return false;
            }
            else
            {
                cnt_d += 1;
            }
        }
        if (cnt_d == 0)
            return false;
        return true;
    }

public:
    bool isNumber(string s)
    {
        if (isInteger(s) || isDecimal(s) || _isNumber(s))
            return true;
        return false;
    }
};

int main()
{

    return 0;
}
