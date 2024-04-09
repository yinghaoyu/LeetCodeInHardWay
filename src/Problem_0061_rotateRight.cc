#include <vector>

using namespace std;

struct ListNode
{
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution
{
 public:
  // 反转链表
  ListNode* reverse(ListNode* head)
  {
    ListNode* pre = nullptr;
    ListNode* cur = head;
    ListNode* next = nullptr;
    while (cur != nullptr)
    {
      next = cur->next;
      cur->next = pre;
      pre = cur;
      cur = next;
    }
    return pre;
  }

  ListNode* rotateRight(ListNode* head, int k)
  {
    if (k == 0 || head == nullptr)
    {
      return head;
    }
    int n = 0;
    ListNode* cur = head;
    // 求链表一共多少个节点
    while (cur != nullptr)
    {
      n++;
      cur = cur->next;
    }

    k %= n;
    k = n - k;
    cur = head;
    ListNode* pre = nullptr;
    while (k-- != 0)
    {
      pre = cur;
      cur = cur->next;
    }
    // 断开链表
    pre->next = nullptr;
    // 反转前 n - k 个
    ListNode* l = reverse(head);
    // 反转后 k 个
    ListNode* r = reverse(cur);
    cur = l;
    while (cur != nullptr)
    {
      pre = cur;
      cur = cur->next;
    }
    // 拼接链表
    pre->next = r;
    // 反转整个链表
    r = reverse(l);
    return r;
  }
};
