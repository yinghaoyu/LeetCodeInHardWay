#include <queue>
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
  class cmp
  {
   public:
    bool operator()(ListNode *l, ListNode *r) { return l->val > r->val; }
  };

  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
    priority_queue<ListNode *, vector<ListNode *>, cmp> heap;
    for (auto &e : lists)
    {
      if (e != nullptr)
      {
        heap.push(e);
      }
    }
    if (heap.empty())
    {
      return nullptr;
    }
    ListNode *head = heap.top();
    ListNode *pre = head;
    heap.pop();
    if(pre->next != nullptr)
    {
      heap.push(pre->next);
    }
    while (!heap.empty())
    {
      ListNode *cur = heap.top();
      heap.pop();
      pre->next = cur;
      pre = cur;
      if (cur->next != nullptr)
      {
        heap.push(cur->next);
      }
    }
    return head;
  }
};

bool isListNodeValueEuqal(ListNode *a, ListNode *b)
{
  if (a == nullptr && b == nullptr)
  {
    return true;
  }
  if (a == nullptr && b != nullptr)
  {
    return false;
  }
  if (a != nullptr && b == nullptr)
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

void testMergeKLists()
{
  Solution s;
  ListNode *x3 = new ListNode(5, nullptr);
  ListNode *x2 = new ListNode(4, x3);
  ListNode *x1 = new ListNode(1, x2);

  ListNode *y3 = new ListNode(4, nullptr);
  ListNode *y2 = new ListNode(3, y3);
  ListNode *y1 = new ListNode(1, y2);

  ListNode *z2 = new ListNode(6, nullptr);
  ListNode *z1 = new ListNode(2, z2);

  vector<ListNode *> n1 = {x1, y1, z1};
  vector<ListNode *> n2 = {nullptr};

  ListNode *s8 = new ListNode(6, nullptr);
  ListNode *s7 = new ListNode(5, s8);
  ListNode *s6 = new ListNode(4, s7);
  ListNode *s5 = new ListNode(4, s6);
  ListNode *s4 = new ListNode(3, s5);
  ListNode *s3 = new ListNode(2, s4);
  ListNode *s2 = new ListNode(1, s3);
  ListNode *s1 = new ListNode(1, s2);

  EXPECT_TRUE(isListNodeValueEuqal(s1, s.mergeKLists(n1)));
  EXPECT_TRUE(isListNodeValueEuqal(nullptr, s.mergeKLists(n2)));
  EXPECT_SUMMARY;
}

int main()
{
  testMergeKLists();
  return 0;
}
