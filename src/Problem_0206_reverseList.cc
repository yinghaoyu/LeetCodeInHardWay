#include <iostream>

#include "UnitTest.h"

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
  ListNode *reverseList(ListNode *head)
  {
    ListNode *pre = nullptr;
    ListNode *next = nullptr;
    while (head != nullptr)
    {
      next = head->next;
      head->next = pre;
      pre = head;
      head = next;
    }
    return pre;
  }
};

bool isListEuqal(ListNode *head1, ListNode *head2)
{
  if (head1 == nullptr && head2 == nullptr)
  {
    return true;
  }
  while (head1 != nullptr && head2 != nullptr)
  {
    if (head1->val != head2->val)
    {
      return false;
    }
    head1 = head1->next;
    head2 = head2->next;
  }
  return head1 == nullptr && head2 == nullptr;
}

void testReverseList()
{
  Solution s;
  ListNode *x5 = new ListNode(5);
  ListNode *x4 = new ListNode(4);
  ListNode *x3 = new ListNode(3);
  ListNode *x2 = new ListNode(2);
  ListNode *x1 = new ListNode(1);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;
  x4->next = x5;

  ListNode *o5 = new ListNode(1);
  ListNode *o4 = new ListNode(2);
  ListNode *o3 = new ListNode(3);
  ListNode *o2 = new ListNode(4);
  ListNode *o1 = new ListNode(5);
  o1->next = o2;
  o2->next = o3;
  o3->next = o4;
  o4->next = o5;

  EXPECT_TRUE(isListEuqal(x1, s.reverseList(o1)));
  EXPECT_SUMMARY;
}

int main()
{
  testReverseList();
  return 0;
}
