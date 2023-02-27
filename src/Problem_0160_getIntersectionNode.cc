#include <iostream>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution
{
 public:
  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
  {
    if (headA == nullptr || headB == nullptr)
    {
      return nullptr;
    }
    ListNode *cur1 = headA;
    ListNode *cur2 = headB;
    int n = 0;
    while (cur1->next != nullptr)
    {
      n++;
      cur1 = cur1->next;
    }
    // cur1 -> end1
    while (cur2->next != nullptr)
    {
      n--;
      cur2 = cur2->next;
    }
    // cur2 -> end2
    if (cur1 != cur2)
    {
      return nullptr;
    }
    cur1 = n > 0 ? headA : headB;  // 谁是长链表，谁把头节点，给cur1赋值
    cur2 = cur1 == headA ? headB : headA;
    n = std::abs(n);
    while (n != 0)
    {
      n--;
      cur1 = cur1->next;
    }
    while (cur1 != cur2)
    {
      cur1 = cur1->next;
      cur2 = cur2->next;
    }
    return cur1;
  }
};
