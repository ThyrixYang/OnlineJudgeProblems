#include <bits/stdc++.h>

using namespace std;

class Solution
{
    static const int MAXN = 7e5;
    vector<bool> value;
    map<vector<int>, bool> dp;
    vector<vector<int>> ch;
    int np;
    void insert(int n, string s, int p)
    {
        // cout << "insert " << n << " " << s << " " << p << endl;
        if (p == s.length())
        {
            value[n] = 1;
            return;
        }
        int v = s[p] - 'a';
        if (ch[n][v] < 0)
        {
            ch[n][v] = np++;
        }
        insert(ch[n][v], s, p + 1);
    }

    bool check(int n, string w, int p)
    {
        // cout << n << " " << w << " " << p << endl;
        vector<int> dpc = {n, p};
        if (dp.find(dpc) != dp.end())
            return dp[dpc];
        if (p == w.length())
        {
            if (value[n])
            {
                return dp[dpc] = true;
            }
            else
            {
                return dp[dpc] = false;
            }
        }
        int v = w[p] - 'a';
        if (ch[n][v] >= 0)
        {
            if (check(ch[n][v], w, p + 1))
                return dp[dpc] = true;
        }
        if (value[n])
        {
            int v = w[p] - 'a';
            if (ch[0][v] >= 0)
            {
                if (check(ch[0][v], w, p + 1))
                    return dp[dpc] = true;
            }
        }
        return dp[dpc] = false;
    }

    static bool cmp(const string &a, const string &b)
    {
        return a.length() < b.length();
    }

public:
    vector<string> findAllConcatenatedWordsInADict(vector<string> &words)
    {
        np = 1;
        value = vector<bool>(MAXN, 0);
        ch = vector<vector<int>>(MAXN, vector<int>(26, -1));
        sort(words.begin(), words.end(), cmp);
        vector<string> ans;
        for (int i = 0; i < words.size(); i++)
        {
            dp.clear();
            if (check(0, words[i], 0))
            {
                ans.push_back(words[i]);
            }
            insert(0, words[i], 0);
        }
        return ans;
    }
};

int main()
{

    vector<string> words = {"cat", "cats", "catsdogcats", "dog", "dogcatsdog", "hippopotamuses", "rat", "ratcatdogcat"};
    Solution sol;
    vector<string> ans = sol.findAllConcatenatedWordsInADict(words);
    for (auto &s : ans)
    {
        cout << s << endl;
    }
    return 0;
}