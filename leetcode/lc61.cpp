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

class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        int len = 0;
        if (head == nullptr)
            return head;
        ListNode *t_head = head;
        while (t_head != nullptr)
        {
            len++;
            t_head = t_head->next;
        }
        if (k % len == 0)
            return head;
        k = len - (k % len);
        t_head = head;
        for (int i = 0; i < k - 1; i++)
        {
            t_head = t_head->next;
        }
        ListNode *new_head = t_head->next;
        t_head->next = nullptr;
        t_head = new_head;
        while (t_head->next != nullptr)
            t_head = t_head->next;
        t_head->next = head;
        return new_head;
    }
};

int main()
{

    return 0;
}