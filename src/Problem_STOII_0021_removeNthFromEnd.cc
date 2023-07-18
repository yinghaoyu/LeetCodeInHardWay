#include <iostream>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// same as leetcode 0019
// https://leetcode-cn.com/problems/remove-nth-node-from-end-of-list/
// see at Problem_0019_removeNthFromEnd.cc
class Solution
{
 public:
  ListNode *removeNthFromEnd(ListNode *head, int n)
  {
    if (head == nullptr)
    {
      return nullptr;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    ListNode *pre = nullptr;
    while (fast != nullptr && n--)
    {
      fast = fast->next;
    }
    if (fast == nullptr)
    {
      return head->next;
    }
    while (fast != nullptr)
    {
      fast = fast->next;
      pre = slow;
      slow = slow->next;
    }
    pre->next = slow->next;
    return head;
  }
};
