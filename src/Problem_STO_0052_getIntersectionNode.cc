#include <iostream>

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
 public:
  int len(ListNode *head)
  {
    int ans = 0;
    while (head != nullptr)
    {
      ans++;
      head = head->next;
    }
    return ans;
  }

  ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
  {
    int n = len(headA);
    int m = len(headB);
    ListNode *longest = n > m ? headA : headB;
    ListNode *smallest = longest == headA ? headB : headA;
    int s = n > m ? n - m : m - n;
    while (s--)
    {
      longest = longest->next;
    }
    while (longest != nullptr && smallest != nullptr)
    {
      if (longest == smallest)
      {
        return longest;
      }
      longest = longest->next;
      smallest = smallest->next;
    }
    return nullptr;
  }
};
