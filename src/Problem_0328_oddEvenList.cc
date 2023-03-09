#include <iostream>
#include <vector>

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
  ListNode *oddEvenList(ListNode *head)
  {
    ListNode *firstOdd = nullptr;
    ListNode *firstEven = nullptr;
    ListNode *odd = nullptr;
    ListNode *even = nullptr;
    ListNode *next = nullptr;
    int count = 1;
    while (head != nullptr)
    {
      next = head->next;
      head->next = nullptr;
      if (count & 1)
      {
        firstOdd = firstOdd == nullptr ? head : firstOdd;
        if (odd != nullptr)
        {
          odd->next = head;
        }
        odd = head;
      }
      else
      {
        firstEven = firstEven == nullptr ? head : firstEven;
        if (even != nullptr)
        {
          even->next = head;
        }
        even = head;
      }
      count++;
      head = next;
    }
    if (odd != nullptr)
    {
      odd->next = firstEven;
    }
    return firstOdd != nullptr ? firstOdd : firstEven;
  }
};

bool isListEqual(ListNode *head1, ListNode *head2)
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
  return head1 == head2;
}

void testOddEvenList()
{
  Solution s;
  ListNode *x5 = new ListNode(5, nullptr);
  ListNode *x4 = new ListNode(4, x5);
  ListNode *x3 = new ListNode(3, x4);
  ListNode *x2 = new ListNode(2, x3);
  ListNode *x1 = new ListNode(1, x2);

  ListNode *o5 = new ListNode(4, nullptr);
  ListNode *o4 = new ListNode(2, o5);
  ListNode *o3 = new ListNode(5, o4);
  ListNode *o2 = new ListNode(3, o3);
  ListNode *o1 = new ListNode(1, o2);

  ListNode *y7 = new ListNode(7, nullptr);
  ListNode *y6 = new ListNode(4, y7);
  ListNode *y5 = new ListNode(6, y6);
  ListNode *y4 = new ListNode(5, y5);
  ListNode *y3 = new ListNode(3, y4);
  ListNode *y2 = new ListNode(1, y3);
  ListNode *y1 = new ListNode(2, y2);

  ListNode *z7 = new ListNode(4, nullptr);
  ListNode *z6 = new ListNode(5, z7);
  ListNode *z5 = new ListNode(1, z6);
  ListNode *z4 = new ListNode(7, z5);
  ListNode *z3 = new ListNode(6, z4);
  ListNode *z2 = new ListNode(3, z3);
  ListNode *z1 = new ListNode(2, z2);
  EXPECT_TRUE(isListEqual(o1, s.oddEvenList(x1)));
  EXPECT_TRUE(isListEqual(z1, s.oddEvenList(y1)));
  EXPECT_SUMMARY;
}

int main()
{
  testOddEvenList();
  return 0;
}
