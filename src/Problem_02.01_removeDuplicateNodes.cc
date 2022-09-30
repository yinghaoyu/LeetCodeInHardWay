#include <iostream>
#include "UnitTest.h"

using namespace std;

class ListNode
{
 public:
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
 public:
  ListNode *removeDuplicateNodes(ListNode *head)
  {
    bool seen[20001] = {false};
    ListNode *pre = nullptr;
    ListNode *cur = head;
    while (cur != nullptr)
    {
      if (seen[cur->val])
      {
        pre->next = cur->next;
        delete cur;
        cur = pre->next;
      }
      else
      {
        seen[cur->val] = true;
        pre = cur;
        cur = cur->next;
      }
    }
    return head;
  }
};

bool isListEqual(ListNode *a, ListNode *b)
{
  while (a != nullptr && b != nullptr)
  {
    if (a->val != b->val)
    {
      return false;
    }
    a = a->next;
    b = b->next;
  }
  return a == nullptr && b == nullptr ? true : false;
}

void testRemoveDuplicateNodes()
{
  Solution s;
  ListNode *x1 = new ListNode(1);
  ListNode *x2 = new ListNode(2);
  ListNode *x3 = new ListNode(3);
  ListNode *x4 = new ListNode(3);
  ListNode *x5 = new ListNode(2);
  ListNode *x6 = new ListNode(1);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;
  x4->next = x5;
  x5->next = x6;

  ListNode *x7 = new ListNode(1);
  ListNode *x8 = new ListNode(2);
  ListNode *x9 = new ListNode(3);
  x7->next = x8;
  x8->next = x9;

  ListNode *y1 = new ListNode(1);
  ListNode *y2 = new ListNode(1);
  ListNode *y3 = new ListNode(1);
  ListNode *y4 = new ListNode(1);
  ListNode *y5 = new ListNode(2);
  y1->next = y2;
  y2->next = y3;
  y3->next = y4;
  y4->next = y5;

  ListNode *y6 = new ListNode(1);
  ListNode *y7 = new ListNode(2);
  y6->next = y7;

  EXPECT_TRUE(isListEqual(x7, s.removeDuplicateNodes(x1)));
  EXPECT_TRUE(isListEqual(y6, s.removeDuplicateNodes(y1)));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveDuplicateNodes();
  return 0;
}
