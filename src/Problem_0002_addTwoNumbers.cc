#include <cstddef>
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
  ListNode *reverse(ListNode *head)
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

  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
  {
    int carry = 0;
    int n1 = 0;
    int n2 = 0;
    int n = 0;
    ListNode *c1 = l1;
    ListNode *c2 = l2;
    ListNode *node = nullptr;
    ListNode *pre = nullptr;
    while (c1 != nullptr || c2 != nullptr)
    {
      n1 = c1 != nullptr ? c1->val : 0;
      n2 = c2 != nullptr ? c2->val : 0;
      n = n1 + n2 + carry;
      pre = node;
      node = new ListNode(n % 10);
      node->next = pre;
      carry = n / 10;
      c1 = c1 != nullptr ? c1->next : nullptr;
      c2 = c2 != nullptr ? c2->next : nullptr;
    }
    if (carry == 1)
    {
      pre = node;
      node = new ListNode(1);
      node->next = pre;
    }
    return reverse(node);
  }
};

bool isListValueEqual(ListNode *a, ListNode *b)
{
  if (a == nullptr && b == nullptr)
  {
    return true;
  }
  if (a == nullptr || b == nullptr)
  {
    return false;
  }
  while (a != nullptr && b != nullptr)
  {
    if (a->val != b->val)
    {
      return false;
    }
    a = a->next;
    b = b->next;
  }
  return true;
}

void testAddTwoNumbers()
{
  Solution s;
  ListNode *a3 = new ListNode(3, nullptr);
  ListNode *a2 = new ListNode(4, a3);
  ListNode *a1 = new ListNode(2, a2);
  ListNode *b3 = new ListNode(4, nullptr);
  ListNode *b2 = new ListNode(6, b3);
  ListNode *b1 = new ListNode(5, b2);
  ListNode *c3 = new ListNode(8, nullptr);
  ListNode *c2 = new ListNode(0, c3);
  ListNode *c1 = new ListNode(7, c2);

  ListNode *x = new ListNode(0, nullptr);
  ListNode *y = new ListNode(0, nullptr);
  ListNode *z = new ListNode(0, nullptr);

  ListNode *i7 = new ListNode(9, nullptr);
  ListNode *i6 = new ListNode(9, i7);
  ListNode *i5 = new ListNode(9, i6);
  ListNode *i4 = new ListNode(9, i5);
  ListNode *i3 = new ListNode(9, i4);
  ListNode *i2 = new ListNode(9, i3);
  ListNode *i1 = new ListNode(9, i2);

  ListNode *j4 = new ListNode(9, nullptr);
  ListNode *j3 = new ListNode(9, j4);
  ListNode *j2 = new ListNode(9, j3);
  ListNode *j1 = new ListNode(9, j2);

  ListNode *k8 = new ListNode(1, nullptr);
  ListNode *k7 = new ListNode(0, k8);
  ListNode *k6 = new ListNode(0, k7);
  ListNode *k5 = new ListNode(0, k6);
  ListNode *k4 = new ListNode(9, k5);
  ListNode *k3 = new ListNode(9, k4);
  ListNode *k2 = new ListNode(9, k3);
  ListNode *k1 = new ListNode(8, k2);

  EXPECT_TRUE(isListValueEqual(c1, s.addTwoNumbers(a1, b1)));
  EXPECT_TRUE(isListValueEqual(z, s.addTwoNumbers(x, y)));
  EXPECT_TRUE(isListValueEqual(k1, s.addTwoNumbers(i1, j1)));
  EXPECT_SUMMARY;
}

int main()
{
  testAddTwoNumbers();
  return 0;
}
