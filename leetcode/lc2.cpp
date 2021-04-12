#include <bits/stdc++.h>

using namespace std;

// 模拟加法，数字用链表表示

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *head = new ListNode();
        ListNode *ans_head = head;
        ListNode *last_head = head;
        int inc = 0;
        while (1)
        {
            int add1 = 0;
            int add2 = 0;
            if (l1 != nullptr)
                add1 = l1->val;
            if (l2 != nullptr)
                add2 = l2->val;
            int add_val = add1 + add2 + inc;
            if (add_val == 0 && l1 == nullptr && l2 == nullptr)
            {
                last_head->next = nullptr;
                break;
            }
            int nv = add_val % 10;
            int nc = add_val / 10;
            head->val = nv;
            inc = nc;
            if (l1 == nullptr && l2 == nullptr && inc == 0)
                break;
            if (l1 != nullptr)
                l1 = l1->next;
            if (l2 != nullptr)
                l2 = l2->next;
            last_head = head;
            head->next = new ListNode();
            head = head->next;
        }
        return ans_head;
    }
};

int main()
{

    return 0;
}