#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/merge-k-sorted-lists/
// @sa Problem_0023_mergeKLists.cc

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
 private:
  class cmp
  {
   public:
    bool operator()(ListNode *a, ListNode *b) { return a->val > b->val; }
  };

 public:
  ListNode *mergeKLists(vector<ListNode *> &lists)
  {
    priority_queue<ListNode *, vector<ListNode *>, cmp> q;
    for (auto &e : lists)
    {
      if (e != nullptr)
      {
        q.push(e);
      }
    }
    if (q.empty())
    {
      return nullptr;
    }
    ListNode *head = q.top();
    ListNode *pre = head;
    q.pop();
    if (pre->next != nullptr)
    {
      q.push(pre->next);
    }
    while (!q.empty())
    {
      ListNode *cur = q.top();
      q.pop();
      pre->next = cur;
      pre = cur;
      if (cur->next != nullptr)
      {
        q.push(cur->next);
      }
    }
    return head;
  }
};
