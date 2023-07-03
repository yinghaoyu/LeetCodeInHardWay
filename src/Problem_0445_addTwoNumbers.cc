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
  ListNode *reverse(ListNode *root)
  {
    ListNode *pre = nullptr;
    ListNode *cur = root;
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

  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
  {
    ListNode *r1 = reverse(l1);
    ListNode *r2 = reverse(l2);
    int carry = 0;
    int sum = 0;
    ListNode *root = new ListNode();
    while (r1 != nullptr || r2 != nullptr)
    {
      int v1 = r1 != nullptr ? r1->val : 0;
      int v2 = r2 != nullptr ? r2->val : 0;
      sum = v1 + v2 + carry;
      carry = sum / 10;
      ListNode *x = new ListNode(sum % 10, root->next);
      root->next = x;
      r1 = r1 != nullptr ? r1->next : r1;
      r2 = r2 != nullptr ? r2->next : r2;
    }
    if (carry)
    {
      ListNode *x = new ListNode(carry, root->next);
      root->next = x;
    }
    return root->next;
  }
};

bool isListEqual(ListNode *l1, ListNode *l2)
{
  while (l1 != nullptr && l2 != nullptr)
  {
    if (l1->val != l2->val)
    {
      return false;
    }
    l1 = l1->next;
    l2 = l2->next;
  }
  return l1 == nullptr && l2 == nullptr;
}

void test()
{
  Solution s;
  ListNode *x4 = new ListNode(3, nullptr);
  ListNode *x3 = new ListNode(4, x4);
  ListNode *x2 = new ListNode(2, x3);
  ListNode *x1 = new ListNode(7, x2);

  ListNode *y3 = new ListNode(4, nullptr);
  ListNode *y2 = new ListNode(6, y3);
  ListNode *y1 = new ListNode(5, y2);

  ListNode *o4 = new ListNode(7, nullptr);
  ListNode *o3 = new ListNode(0, o4);
  ListNode *o2 = new ListNode(8, o3);
  ListNode *o1 = new ListNode(7, o2);

  EXPECT_TRUE(isListEqual(o1, s.addTwoNumbers(x1, y1)));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
