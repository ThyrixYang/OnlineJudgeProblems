#include <bits/stdc++.h>

using namespace std;

//链表模拟，每k个元素翻转，O(1)空间，O(k+n)复杂度

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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *ans_head = nullptr;
        ListNode *ans_back = nullptr;
        ListNode *p_head = head;
        ListNode *p_back = head;
        head = head->next;
        int cnt = 1;
        while (true)
        {
            if (cnt % k == 0 || head == nullptr)
            {
                if (head == nullptr && cnt < k)
                {
                    p_back->next = nullptr;
                    ListNode *reversed_p_head = reverseKGroup(p_head, cnt);
                    ListNode *reversed_p_back = reversed_p_head;
                    while (reversed_p_back->next != nullptr)
                    {
                        reversed_p_back = reversed_p_back->next;
                    }
                    p_back = reversed_p_back;
                    p_head = reversed_p_head;
                }
                if (ans_head == nullptr)
                {
                    ans_head = p_head;
                    ans_back = p_back;
                }
                else
                {
                    ans_back->next = p_head;
                    ans_back = p_back;
                }
                if (head == nullptr)
                    break;
                p_head = head;
                p_back = head;
                head = head->next;
                cnt = 1;
                continue;
            }
            ListNode *next = head->next;
            head->next = p_head;
            p_head = head;
            head = next;
            cnt += 1;
        }
        ans_back->next = nullptr;
        return ans_head;
    }
};

int main()
{

    return 0;
}