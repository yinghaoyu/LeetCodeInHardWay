#include <iostream>
#include <vector>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// same as leetcode 0234
// https://leetcode-cn.com/problems/palindrome-linked-list/
// see at Problem_0234_isPalindrome.cc
class Solution
{
 public:
  ListNode *reverseList(ListNode *head)
  {
    ListNode *pre = nullptr;
    ListNode *cur = head;
    ListNode *next = nullptr;
    while (cur != nullptr)
    {
      next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }

  bool isPalindrome(ListNode *head)
  {
    if (head == nullptr || head->next == nullptr)
    {
      return true;
    }
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast->next != nullptr && fast->next->next != nullptr)
    {
      fast = fast->next->next;
      slow = slow->next;
    }
    ListNode *down = slow->next;
    slow->next = nullptr;
    ListNode *p1 = head;
    ListNode *p2 = reverseList(down);
    bool ans = true;
    while (p1 != nullptr && p2 != nullptr)
    {
      if (p1->val != p2->val)
      {
        ans = false;
        break;
      }
      p1 = p1->next;
      p2 = p2->next;
    }
    slow->next = reverseList(p2);
    return ans;
  }
};
