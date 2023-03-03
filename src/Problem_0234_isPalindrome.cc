#include <functional>
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
  ListNode *reverse(ListNode *node)
  {
    ListNode *pre = nullptr;
    ListNode *next = nullptr;
    while (node != nullptr)
    {
      next = node->next;
      node->next = pre;
      pre = node;
      node = next;
    }
    return pre;
  }

  bool isMirror(ListNode *head1, ListNode *head2)
  {
    while (head1 != nullptr && head2 != nullptr)
    {
      if (head1->val != head2->val)
      {
        return false;
      }
      head1 = head1->next;
      head2 = head2->next;
    }
    return true;
  }

  // 翻转链表，空间复杂度O(1)
  bool isPalindrome1(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
    {
      return true;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    // 断开左右链表
    fast = slow->next;
    slow->next = nullptr;
    // 翻转
    ListNode *p = reverse(fast);
    bool ans = isMirror(head, p);
    // 恢复
    ListNode *q = reverse(p);
    slow->next = q;
    return ans;
  }

  // 递归
  bool isPalindrome2(ListNode *head)
  {
    ListNode *peer = head;
    auto rec = [&](auto &self, ListNode *cur) -> bool {
      if (cur != nullptr)
      {
        if (!self(self, cur->next))
        {
          return false;
        }
        if (cur->val != peer->val)
        {
          return false;
        }
        peer = peer->next;
      }
      return true;
    };
    return rec(rec, head);
  }
};

void testIsPalindrome()
{
  Solution s;
  ListNode *h4 = new ListNode(1, nullptr);
  ListNode *h3 = new ListNode(2, h4);
  ListNode *h2 = new ListNode(2, h3);
  ListNode *h1 = new ListNode(1, h2);

  ListNode *r2 = new ListNode(1, nullptr);
  ListNode *r1 = new ListNode(1, r1);
  EXPECT_TRUE(s.isPalindrome1(h1));
  EXPECT_FALSE(s.isPalindrome1(r1));
  EXPECT_TRUE(s.isPalindrome2(h1));
  EXPECT_FALSE(s.isPalindrome2(r1));
  EXPECT_SUMMARY;
}

int main()
{
  testIsPalindrome();
  return 0;
}
