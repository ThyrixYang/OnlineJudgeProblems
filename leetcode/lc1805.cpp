#include <bits/stdc++.h>

using namespace std;

// 简单模拟

class Solution
{
public:
    int numDifferentIntegers(string word)
    {
        set<string> a;
        string t = "";
        int lz = 0;
        for (int i = 0; i < word.length(); i++)
        {
            char c = word[i];
            if (c >= '0' && c <= '9')
            {
                if (c == '0' && t.length() == 0)
                {
                    lz = 1;
                }
                else
                {
                    t.push_back(c);
                }
            }
            else
            {
                if (t.length() > 0 || lz == 1)
                {
                    if (t.length() > 0)
                    {
                        a.insert(t);
                    }
                    else
                    {
                        a.insert("0");
                    }
                }
                lz = 0;
                t = "";
            }
        }
        if (t.length() > 0)
        {
            a.insert(t);
        }
        else if (lz > 0)
        {
            a.insert("0");
        }
        return a.size();
    }
};

int main()
{

    return 0;
}