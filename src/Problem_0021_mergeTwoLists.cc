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
  ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
  {
    if (list1 == nullptr || list2 == nullptr)
    {
      return list1 == nullptr ? list2 : list1;
    }
    // 先确定head
    ListNode *head = list1->val <= list2->val ? list1 : list2;
    ListNode *cur1 = head->next;
    ListNode *cur2 = head == list1 ? list2 : list1;
    ListNode *pre = head;
    while (cur1 != nullptr && cur2 != nullptr)
    {
      if (cur1->val <= cur2->val)
      {
        pre->next = cur1;
        cur1 = cur1->next;
      }
      else
      {
        pre->next = cur2;
        cur2 = cur2->next;
      }
      pre = pre->next;
    }
    pre->next = cur1 != nullptr ? cur1 : cur2;
    return head;
  }
};

bool isListValueEuqal(ListNode *a, ListNode *b)
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
  return true;
}

void testMergeTwoLists()
{
  Solution s;

  ListNode *x3 = new ListNode(4, nullptr);
  ListNode *x2 = new ListNode(2, x3);
  ListNode *x1 = new ListNode(1, x2);

  ListNode *y3 = new ListNode(4, nullptr);
  ListNode *y2 = new ListNode(3, y3);
  ListNode *y1 = new ListNode(1, y2);

  ListNode *z6 = new ListNode(4, nullptr);
  ListNode *z5 = new ListNode(4, nullptr);
  ListNode *z4 = new ListNode(3, z5);
  ListNode *z3 = new ListNode(2, z4);
  ListNode *z2 = new ListNode(1, z3);
  ListNode *z1 = new ListNode(1, z2);

  EXPECT_TRUE(isListValueEuqal(z1, s.mergeTwoLists(x1, y1)));
  EXPECT_SUMMARY;
}

int main()
{
  testMergeTwoLists();
  return 0;
}
