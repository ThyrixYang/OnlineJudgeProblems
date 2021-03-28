#include <bits/stdc++.h>

using namespace std;

class Solution
{
    struct Node
    {
        Node *ch[26];
        string value;
        Node()
        {
            memset(ch, 0, sizeof(ch));
        }
    };
    Node *root;
    void insert(string k, string v)
    {
        Node *n = root;
        for (auto c : k)
        {
            int cc = c - 'a';
            if (!n->ch[cc])
            {
                n->ch[cc] = new Node();
            }
            n = n->ch[cc];
        }
        n->value = v;
    }

public:
    string evaluate(string s, vector<vector<string>> &knowledge)
    {
        char *ans_s = new char[1000005];
        int ans_p = 0;
        root = new Node();
        for (auto v : knowledge)
        {
            insert(v[0], v[1]);
        }
        int on_key = 0;
        Node *now = root;
        for (auto a : s)
        {
            if (a == '(')
            {
                on_key = 1;
            }
            else if (a == ')')
            {
                if (now->value.length() > 0 && on_key == 1)
                {
                    for (auto c : now->value)
                    {
                        ans_s[ans_p++] = c;
                    }
                }
                else
                {
                    ans_s[ans_p++] = '?';
                }
                on_key = 0;
                now = root;
            }
            else if (on_key == 2)
            {
                continue;
            }
            else if (on_key == 1)
            {
                int cc = a - 'a';
                if (now->ch[cc])
                {
                    now = now->ch[cc];
                }
                else
                {
                    on_key = 2;
                }
            }
            else
            {
                ans_s[ans_p++] = a;
            }
        }
        ans_s[ans_p] = 0;
        return string(ans_s);
    }
};

int main()
{

    return 0;
}