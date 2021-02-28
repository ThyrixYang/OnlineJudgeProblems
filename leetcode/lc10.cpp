#include <bits/stdc++.h>

using namespace std;

map<string, int> M;

bool isMatch(string s, string p)
{
    string key = s + "$" + p;
    if (M.find(key) != M.end())
        return M[key];
    bool ans = false;

    if (s.length() == 0 && p.length() == 0)
        return true;
    if (s.length() > 0 && p.length() == 0)
        return false;
    if (p.length() >= 2 && p[1] == '*')
    {
        if (s.length() == 0)
            ans |= isMatch(s, p.substr(2));
        else if (p[0] == '.')
        {
            ans |= isMatch(s.substr(1), p.substr(2)) || isMatch(s, p.substr(2)) || isMatch(s.substr(1), p);
        }
        else
        {
            if (s[0] == p[0])
            {
                ans |= isMatch(s.substr(1), p.substr(2)) || isMatch(s, p.substr(2)) || isMatch(s.substr(1), p);
            }
            else
            {
                ans |= isMatch(s, p.substr(2));
            }
        }
    }
    else
    {
        if (s.length() == 0)
            return false;
        if (s[0] == p[0] || p[0] == '.')
        {
            ans |= isMatch(s.substr(1), p.substr(1));
        }
    }
    return M[key] = ans;
}

int main()
{
    string s = "mississippi";
    string p = "mis*is*.p*.";
    cout << isMatch(s, p) << endl;

    return 0;
}