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
 private:
  // 一般链表翻转
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

 public:
  ListNode* reverseBetween(ListNode* head, int left, int right)
  {
    // 引入dummy节点简化代码
    ListNode* dummy = new ListNode(-1);
    dummy->next = head;
    ListNode* pre = dummy;
    for (int i = 0; i < left - 1; i++)
    {
      pre = pre->next;
    }

    ListNode* cur = pre->next;
    ListNode* next = nullptr;
    for (int i = 0; i < right - left; i++)
    {
      // 与前面的reverse函数异曲同工
      next = cur->next;
      cur->next = next->next;
      next->next = pre->next;
      pre->next = next;
    }
    return dummy->next;
  }
};
