#include <unordered_set>
#include <vector>

using namespace std;

truct ListNode
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
  ListNode* modifiedList(vector<int>& nums, ListNode* head)
  {
    unordered_set<int> set(nums.begin(), nums.end());

    ListNode dummy(0, head);

    ListNode* cur = &dummy;

    while (cur->next)
    {
      ListNode* next = cur->next;
      if (set.count(next->val))
      {
        cur->next = next->next;
      }
      else
      {
        cur = next;
      }
    }

    return dummy.next;
  }
};
