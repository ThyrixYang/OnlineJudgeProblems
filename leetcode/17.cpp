#include <bits/stdc++.h>

using namespace std;

// dfs输出

class Solution
{
    vector<string> ans;
    map<int, vector<int>> M;
    void dfs(int p, string s, string dig)
    {
        if (p == dig.length())
        {
            if (s.length() > 0)
                ans.push_back(s);
            return;
        }
        for (char c : M[dig[p] - '0'])
        {
            s.push_back(c);
            dfs(p + 1, s, dig);
            s.pop_back();
        }
    }

public:
    vector<string> letterCombinations(string digits)
    {
        M[1] = vector<int>();
        M[2] = vector<int>{'a', 'b', 'c'};
        M[3] = vector<int>{'d', 'e', 'f'};
        M[4] = vector<int>{'g', 'h', 'i'};
        M[5] = vector<int>{'j', 'k', 'l'};
        M[6] = vector<int>{'m', 'n', 'o'};
        M[7] = vector<int>{'p', 'q', 'r', 's'};
        M[8] = vector<int>{'t', 'u', 'v'};
        M[9] = vector<int>{'w', 'x', 'y', 'z'};
        dfs(0, string(), digits);
        return ans;
    }
};

int main()
{

    return 0;
}