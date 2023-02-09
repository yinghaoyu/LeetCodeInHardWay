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
  ListNode *mergeInBetween(ListNode *list1, int a, int b, ListNode *list2)
  {
    ListNode *l2e = list2;
    while (l2e != nullptr && l2e->next != nullptr)
    {
      // 找到list2的最后一个节点
      l2e = l2e->next;
    }
    ListNode *l1a = list1;
    ListNode *l1b = list1;
    a--;
    while (l1a != nullptr && a--)
    {
      // 找到list1第a-1个节点
      l1a = l1a->next;
    }
    while (l1a != nullptr && b--)
    {
      // 找到list1第b个节点
      l1b = l1b->next;
    }
    l1a->next = list2;
    l2e->next = l1b->next;
    return list1;
  }
};
