#include <bits/stdc++.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void append(ListNode *n, int value)
{
    while (n->next != nullptr)
    {
        n = n->next;
    }
    n->next = new ListNode(value);
}

class Solution
{
    static const int MAXN = 40000;
    int minValue[MAXN];
    int minPos[MAXN];
    int bottom;
    void update(int pos, int value)
    {
        int p = pos + bottom;
        minValue[p] = value;
        minPos[p] = pos;
        while (true)
        {
            int pp = p ^ 1;
            if (p == 0 || pp == 0)
                break;
            int v, opos;
            if (minValue[p] < minValue[pp])
            {
                v = minValue[p];
                opos = minPos[p];
            }
            else
            {
                v = minValue[pp];
                opos = minPos[pp];
            }
            int o = p / 2;
            minValue[o] = v;
            minPos[o] = opos;
            p = o;
        }
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        for (int i = 0; i < MAXN; i++)
        {
            minValue[i] = 1e5;
        }
        int t = 1;
        while (t < lists.size())
        {
            t *= 2;
        }
        bottom = t;

        for (int i = 0; i < lists.size(); i++)
        {
            if (lists[i] != nullptr)
            {
                update(i, lists[i]->val);
            }
        }
        if (minValue[1] >= 2e4)
        {
            return nullptr;
        }
        ListNode *head = new ListNode(minValue[1]);
        lists[minPos[1]] = lists[minPos[1]]->next;
        if (lists[minPos[1]] == nullptr)
        {
            update(minPos[1], 1e5);
        }
        else
            update(minPos[1], lists[minPos[1]]->val);
        ListNode *last = head;
        while (minValue[1] < 2e4)
        {
            last->next = new ListNode(minValue[1]);
            lists[minPos[1]] = lists[minPos[1]]->next;
            if (lists[minPos[1]] == nullptr)
            {
                update(minPos[1], 1e5);
            }
            else
                update(minPos[1], lists[minPos[1]]->val);
            last = last->next;
        }
        return head;
    }
};

int main()
{
    ListNode *h1 = new ListNode(1);
    ListNode *h2 = new ListNode(1);
    ListNode *h3 = new ListNode(1);
    append(h1, 2);
    append(h2, 3);
    append(h3, 1);
    vector<ListNode *> vec{h1, h2, h3};
    Solution sol;
    ListNode *res = sol.mergeKLists(vec);
    cout << res << endl;
    while (res != nullptr)
    {
        cout << res->val << endl;
        res = res->next;
    }
    return 0;
}