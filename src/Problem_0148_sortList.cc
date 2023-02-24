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
  ListNode *sortList(ListNode *head)
  {
    // 递归结束
    if (head == nullptr || head->next == nullptr)
    {
      return head;
    }
    // 找到链表中间节点并断开链表 & 递归下探
    ListNode *midNode = middleNode(head);
    ListNode *rightNode = midNode->next;
    midNode->next = nullptr;

    ListNode *left = sortList(head);
    ListNode *right = sortList(rightNode);

    // 合并有序链表
    return mergeTwoLists(left, right);
  }

 private:
  ListNode *middleNode(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
    {
      return head;
    }
    ListNode *slow = head;
    ListNode *fast = head->next->next;
    while (fast != nullptr && fast->next != nullptr)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
  }

  ListNode *mergeTwoLists(ListNode *head1, ListNode *head2)
  {
    ListNode *sentry = new ListNode(-1);
    ListNode *cur = sentry;
    while (head1 != nullptr && head2 != nullptr)
    {
      if (head1->val < head2->val)
      {
        cur->next = head1;
        head1 = head1->next;
      }
      else
      {
        cur->next = head2;
        head2 = head2->next;
      }
      cur = cur->next;
    }
    cur->next = head1 != nullptr ? head1 : head2;
    return sentry->next;
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
  return head1 == nullptr && head2 == nullptr;
}

void testSortList()
{
  Solution s;
  ListNode *x1 = new ListNode(4);
  ListNode *x2 = new ListNode(2);
  ListNode *x3 = new ListNode(1);
  ListNode *x4 = new ListNode(3);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;

  ListNode *o1 = new ListNode(1);
  ListNode *o2 = new ListNode(2);
  ListNode *o3 = new ListNode(3);
  ListNode *o4 = new ListNode(4);
  o1->next = o2;
  o2->next = o3;
  o3->next = o4;

  ListNode *y = nullptr;
  ListNode *z = nullptr;

  EXPECT_TRUE(isListEqual(o1, s.sortList(x1)));
  EXPECT_TRUE(isListEqual(z, s.sortList(y)));
  EXPECT_SUMMARY;
}

int main()
{
  testSortList();
  return 0;
}
