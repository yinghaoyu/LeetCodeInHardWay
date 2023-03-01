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
  ListNode *reverseList1(ListNode *head)
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

  // 递归
  // 以 1 -> 2 -> 3 -> 5 为例
  ListNode *reverseList2(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
    {
      // 直到当前节点的下一个节点为空时返回当前节点
      // 由于5没有下一个节点了，所以此处返回节点5

      return head;
    }
    //递归传入下一个节点，目的是为了到达最后一个节点
    ListNode *newHead = reverseList2(head->next);

    // 第一轮出栈，head为5，head.next为空，返回5
    // 第二轮出栈，head为4，head.next为5，执行head.next.next=head也就是5.next=4，
    //       把当前节点的子节点的子节点指向当前节点
    //       此时链表为1->2->3->4<->5，由于4与5互相指向，所以此处要断开4.next=null
    //       此时链表为1->2->3->4<-5
    //       返回节点5
    // 第三轮出栈，head为3，head.next为4，执行head.next.next=head也就是4.next=3，
    //       此时链表为1->2->3<->4<-5，由于3与4互相指向，所以此处要断开3.next=null
    //       此时链表为1->2->3<-4<-5
    //       返回节点5
    // 第四轮出栈，head为2，head.next为3，执行head.next.next=head也就是3.next=2，
    //       此时链表为1->2<->3<-4<-5，由于2与3互相指向，所以此处要断开2.next=null
    //       此时链表为1->2<-3<-4<-5
    //       返回节点5
    // 第五轮出栈，head为1，head.next为2，执行head.next.next=head也就是2.next=1，
    //       此时链表为1<->2<-3<-4<-5，由于1与2互相指向，所以此处要断开1.next=null
    //       此时链表为1<-2<-3<-4<-5
    //       返回节点5
    // 出栈完成，最终头节点5->4->3->2->1

    head->next->next = head;
    head->next = nullptr;
    return newHead;
  }
};

bool isListEuqal(ListNode *head1, ListNode *head2)
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

void testReverseList()
{
  Solution s;
  ListNode *x5 = new ListNode(5);
  ListNode *x4 = new ListNode(4);
  ListNode *x3 = new ListNode(3);
  ListNode *x2 = new ListNode(2);
  ListNode *x1 = new ListNode(1);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;
  x4->next = x5;

  ListNode *o5 = new ListNode(1);
  ListNode *o4 = new ListNode(2);
  ListNode *o3 = new ListNode(3);
  ListNode *o2 = new ListNode(4);
  ListNode *o1 = new ListNode(5);
  o1->next = o2;
  o2->next = o3;
  o3->next = o4;
  o4->next = o5;
  ListNode *r = s.reverseList1(o1);
  EXPECT_TRUE(isListEuqal(x1, r));
  EXPECT_TRUE(isListEuqal(s.reverseList2(x1), s.reverseList2(r)));
  EXPECT_SUMMARY;
}

int main()
{
  testReverseList();
  return 0;
}
