#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// same as leetcode 0143
// https://leetcode-cn.com/problems/reorder-list/
// see at Problem_0143_reorderList.cc
class Solution
{
  ListNode *reverseList(ListNode *head)
  {
    ListNode *pre = nullptr;
    ListNode *cur = head;
    ListNode *next = nullptr;
    while (cur != nullptr)
    {
      next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }

  void reorderList(ListNode *head)
  {
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != nullptr && fast->next != nullptr)
    {
      fast = fast->next->next;
      slow = slow->next;
    }
    ListNode *down = slow->next;
    slow->next = nullptr;
    ListNode *p1 = head;
    ListNode *p2 = reverseList(down);
    while (p1 != nullptr && p2 != nullptr)
    {
      ListNode *next1 = p1->next;
      ListNode *next2 = p2->next;
      p1->next = p2;
      p2->next = next1;
      p1 = next1;
      p2 = next2;
    }
  }
};
