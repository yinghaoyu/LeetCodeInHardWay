#include <iostream>

#include "UnitTest.h"

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
 public:
  bool hasCycle(ListNode *head) { return getFirstLoopNode(head) != nullptr; }
  ListNode *getFirstLoopNode(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
    {
      return nullptr;
    }
    ListNode *slow = head->next;
    ListNode *fast = head->next->next;
    while (slow != fast)
    {
      if (slow->next == nullptr || fast->next->next == nullptr)
      {
        return nullptr;
      }
      slow = slow->next;
      fast = fast->next->next;
    }
    fast = head;
    while (slow != fast)
    {
      slow = slow->next;
      fast = fast->next;
    }
    return slow;
  }
};

void testHasCycle()
{
  Solution s;
  ListNode *x4 = new ListNode(-4);
  ListNode *x3 = new ListNode(0);
  ListNode *x2 = new ListNode(2);
  ListNode *x1 = new ListNode(3);
  x4->next = x2;
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;

  ListNode *y2 = new ListNode(2);
  ListNode *y1 = new ListNode(1);
  y1->next = y2;
  y2->next = y1;

  ListNode *z = new ListNode(1);
  EXPECT_TRUE(s.hasCycle(x1));
  EXPECT_TRUE(s.hasCycle(y1));
  EXPECT_FALSE(s.hasCycle(z));
  EXPECT_SUMMARY;
}

int main()
{
  testHasCycle();
  return 0;
}
