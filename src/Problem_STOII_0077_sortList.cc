#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/sort-list/
// @sa Problem_0148_sortList.cc

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
  ListNode *middleNode(ListNode *node)
  {
    if (node == nullptr || node->next == nullptr)
    {
      return node;
    }
    ListNode *slow = node;
    ListNode *fast = node->next->next;
    while (fast && fast->next)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }
  ListNode *mergeList(ListNode *a, ListNode *b)
  {
    ListNode *dummy = new ListNode(-1);
    ListNode *cur = dummy;
    while (a && b)
    {
      if (a->val < b->val)
      {
        cur->next = a;
        a = a->next;
      }
      else
      {
        cur->next = b;
        b = b->next;
      }
      cur = cur->next;
    }
    cur->next = a != nullptr ? a : b;
    return dummy->next;
  }

  ListNode *sortList(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
    {
      return head;
    }
    ListNode *mid = middleNode(head);
    ListNode *node = mid->next;
    mid->next = nullptr;
    ListNode *left = sortList(head);
    ListNode *right = sortList(node);
    return mergeList(left, right);
  }
};
