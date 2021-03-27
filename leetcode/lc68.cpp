#include <bits/stdc++.h>

using namespace std;

class Solution
{
    string distribute_last(vector<string> words, int maxWidth)
    {
        string ans = "";
        for (int i = 0; i < words.size(); i++)
        {
            if (i < words.size() - 1)
            {
                ans = ans + words[i];
                ans.push_back(' ');
            }
            else
            {
                ans = ans + words[i];
                while (ans.length() < maxWidth)
                    ans.push_back(' ');
            }
        }
        return ans;
    }
    string distribute(vector<string> words, int maxWidth)
    {
        int l_sum = 0;
        int w_cnt = words.size();
        for (auto w : words)
            l_sum += w.length();
        int rm = maxWidth - l_sum;
        if (w_cnt == 1)
        {
            string ans = words[0];
            for (int i = 0; i < rm; i++)
                ans.push_back(' ');
            return ans;
        }
        else
        {
            string ans = "";
            int m_d = rm / (w_cnt - 1);
            int m_c = rm % (w_cnt - 1);
            for (int i = 0; i < w_cnt; i++)
            {
                ans = ans + words[i];
                if (i < w_cnt - 1)
                {
                    if (m_c > 0)
                    {
                        m_c--;
                        for (int j = 0; j < m_d + 1; j++)
                            ans.push_back(' ');
                    }
                    else
                    {
                        for (int j = 0; j < m_d; j++)
                            ans.push_back(' ');
                    }
                }
            }
            return ans;
        }
    }

public:
    vector<string> fullJustify(vector<string> &words, int maxWidth)
    {
        vector<string> ws;
        int word_cnt = 0;
        int word_length = 0;
        vector<string> ans;
        for (int i = 0; i < words.size(); i++)
        {
            string w = words[i];
            int new_word_cnt = word_cnt + 1;
            int new_word_length = word_length + w.length();
            int min_len = new_word_length + new_word_cnt - 1;
            if (min_len > maxWidth)
            {
                // cerr << ws.size() << endl;
                ans.push_back(distribute(ws, maxWidth));
                ws.clear();
                word_cnt = 1;
                word_length = w.length();
                ws.push_back(w);
            }
            else
            {
                ws.push_back(w);
                word_cnt = new_word_cnt;
                word_length = new_word_length;
            }
        }
        ans.push_back(distribute_last(ws, maxWidth));
        return ans;
    }
};

int main()
{
    vector<string> ws = {"What", "must", "be", "acknowledgment", "shall", "be"};
    Solution sol;
    auto res = sol.fullJustify(ws, 16);
    for (auto s : res)
    {
        cerr << s << endl;
    }
    return 0;
}