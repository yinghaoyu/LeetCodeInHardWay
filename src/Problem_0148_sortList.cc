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
  // 归并排序递归解
  ListNode *sortList1(ListNode *head)
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

    ListNode *left = sortList1(head);
    ListNode *right = sortList1(rightNode);

    // 合并有序链表
    return mergeTwoLists(left, right);
  }

  // 归并改循环
  ListNode *sortList2(ListNode *head)
  {
    int N = 0;
    ListNode *cur = head;
    while (cur != nullptr)
    {
      // 获取节点总数
      N++;
      cur = cur->next;
    }
    ListNode *h = head;
    ListNode *teamFirst = head;
    ListNode *pre = nullptr;
    // 对链表分组归并1 2 4 ...
    for (int len = 1; len < N; len <<= 1)
    {
      while (teamFirst != nullptr)
      {
        // 根据长度获取分组，左右分组长度都为len
        vector<ListNode *> ht = hthtn(teamFirst, len);
        // 归并分组
        vector<ListNode *> mhmt = merge(ht[0], ht[1], ht[2], ht[3]);
        if (h == teamFirst)
        {
          h = mhmt[0];
          pre = mhmt[1];
        }
        else
        {
          pre->next = mhmt[0];
          pre = mhmt[1];
        }
        teamFirst = ht[4];
      }
      teamFirst = h;
      pre = nullptr;
    }
    return h;
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

  vector<ListNode *> hthtn(ListNode *teamFirst, int len)
  {
    ListNode *leftStart = teamFirst;
    ListNode *leftEnd = teamFirst;
    ListNode *rightStart = nullptr;
    ListNode *rightEnd = nullptr;
    ListNode *next = nullptr;
    int pass = 0;
    while (teamFirst != nullptr)
    {
      pass++;
      if (pass <= len)
      {
        leftEnd = teamFirst;
      }
      if (pass == len + 1)
      {
        rightStart = teamFirst;
      }
      if (pass > len)
      {
        rightEnd = teamFirst;
      }
      if (pass == (len << 1))
      {
        break;
      }
      teamFirst = teamFirst->next;
    }
    // 断开左右分组链表
    leftEnd->next = nullptr;
    if (rightEnd != nullptr)
    {
      next = rightEnd->next;
      // 断开大组链表
      rightEnd->next = nullptr;
    }
    return {leftStart, leftEnd, rightStart, rightEnd, next};
  }

  vector<ListNode *> merge(ListNode *leftStart, ListNode *leftEnd, ListNode *rightStart, ListNode *rightEnd)
  {
    if (rightStart == nullptr)
    {
      return {leftStart, leftEnd};
    }
    ListNode *head = nullptr;
    ListNode *pre = nullptr;
    ListNode *cur = nullptr;
    ListNode *tail = nullptr;
    while (leftStart != leftEnd->next && rightStart != rightEnd->next)
    {
      if (leftStart->val <= rightStart->val)
      {
        cur = leftStart;
        leftStart = leftStart->next;
      }
      else
      {
        cur = rightStart;
        rightStart = rightStart->next;
      }
      if (pre == nullptr)
      {
        head = cur;
        pre = cur;
      }
      else
      {
        pre->next = cur;
        pre = cur;
      }
    }
    if (leftStart != leftEnd->next)
    {
      while (leftStart != leftEnd->next)
      {
        pre->next = leftStart;
        pre = leftStart;
        tail = leftStart;
        leftStart = leftStart->next;
      }
    }
    else
    {
      while (rightStart != rightEnd->next)
      {
        pre->next = rightStart;
        pre = rightStart;
        tail = rightStart;
        rightStart = rightStart->next;
      }
    }
    return {head, tail};
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

  ListNode *z1 = new ListNode(4);
  ListNode *z2 = new ListNode(2);
  ListNode *z3 = new ListNode(1);
  ListNode *z4 = new ListNode(3);
  z1->next = z2;
  z2->next = z3;
  z3->next = z4;

  ListNode *o1 = new ListNode(1);
  ListNode *o2 = new ListNode(2);
  ListNode *o3 = new ListNode(3);
  ListNode *o4 = new ListNode(4);
  o1->next = o2;
  o2->next = o3;
  o3->next = o4;

  ListNode *y = nullptr;
  ListNode *z = nullptr;

  EXPECT_TRUE(isListEqual(o1, s.sortList1(x1)));
  EXPECT_TRUE(isListEqual(z, s.sortList1(y)));
  EXPECT_TRUE(isListEqual(o1, s.sortList2(z1)));
  EXPECT_TRUE(isListEqual(z, s.sortList2(y)));
  EXPECT_SUMMARY;
}

int main()
{
  testSortList();
  return 0;
}
