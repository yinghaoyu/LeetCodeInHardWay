#include <iostream>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// same as leetcode 0142
// https://leetcode-cn.com/problems/linked-list-cycle-ii/
// see at Problem_0142_detectCycle.cc
class Solution
{
 public:
  ListNode *detectCycle(ListNode *head)
  {
    if (head == nullptr)
    {
      return nullptr;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    do
    {
      if (fast == nullptr || fast->next == nullptr)
      {
        return nullptr;
      }
      fast = fast->next->next;
      slow = slow->next;
    } while (fast != slow);
    fast = head;
    while (fast != slow)
    {
      fast = fast->next;
      slow = slow->next;
    }
    return fast;
  }
};
