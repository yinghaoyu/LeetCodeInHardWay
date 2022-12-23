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
  // 快慢指针
  ListNode *removeNthFromEnd1(ListNode *head, int n)
  {
    ListNode *pre = nullptr;
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != nullptr && n)
    {
      // 快指针先走n步
      fast = fast->next;
      n--;
    }
    if (fast == nullptr)
    {
      // 快指针到结尾了，说明当前慢指针就是要删除的位置
      return head->next;
    }
    while (fast != nullptr)
    {
      pre = slow;
      fast = fast->next;
      slow = slow->next;
    }
    pre->next = slow->next;
    return head;
  }

  // 递归
  ListNode *process(ListNode *node, int &cur, int n)
  {
    if (node == nullptr)
    {
      return nullptr;
    }
    // node 没有走到结尾会一直走
    node->next = process(node->next, cur, n);
    // 当倒数第一个节点返回后，cur++
    cur++;
    if (cur == n)
    {
      // 当前节点是倒数第n个节点
      // 那么给前一个节点返回当前节点的next，相当于删除了当前节点
      return node->next;
    }
    // 给前一个节点返回自己，相当于没做任何操作
    return node;
  }

  ListNode *removeNthFromEnd2(ListNode *head, int n)
  {
    int cur = 0;
    return process(head, cur, n);
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

void testRemoveNthFromEnd()
{
  Solution s;
  ListNode *x5 = new ListNode(5, nullptr);
  ListNode *x4 = new ListNode(4, x5);
  ListNode *x3 = new ListNode(3, x4);
  ListNode *x2 = new ListNode(2, x3);
  ListNode *x1 = new ListNode(1, x2);

  ListNode *y5 = new ListNode(5, nullptr);
  ListNode *y3 = new ListNode(3, y5);
  ListNode *y2 = new ListNode(2, y3);
  ListNode *y1 = new ListNode(1, y2);

  ListNode *z = new ListNode(1, nullptr);
  EXPECT_TRUE(isListValueEuqal(y1, s.removeNthFromEnd2(x1, 2)));
  EXPECT_TRUE(isListValueEuqal(nullptr, s.removeNthFromEnd2(x1, 1)));
  EXPECT_SUMMARY;
}

int main()
{
  testRemoveNthFromEnd();
  return 0;
}
