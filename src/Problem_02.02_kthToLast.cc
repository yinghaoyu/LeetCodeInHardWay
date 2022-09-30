#include <assert.h>
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
  int kthToLast(ListNode *head, int k)
  {
    assert(head != nullptr);
    ListNode *fast = head;
    ListNode *slow = head;
    for (int i = 0; i < k; i++)
    {
      fast = fast->next;
    }
    while (fast != NULL)
    {
      fast = fast->next;
      slow = slow->next;
    }
    return slow->val;
  }
};

void testKthToLast()
{
  Solution s;
  ListNode *x1 = new ListNode(1);
  ListNode *x2 = new ListNode(2);
  ListNode *x3 = new ListNode(3);
  ListNode *x4 = new ListNode(4);
  ListNode *x5 = new ListNode(5);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;
  x4->next = x5;
  EXPECT_EQ_INT(4, s.kthToLast(x1, 2));
  EXPECT_SUMMARY;
}

int main()
{
  testKthToLast();
  return 0;
}
