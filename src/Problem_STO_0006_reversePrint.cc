#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
 public:
  void process(ListNode *x, vector<int> &ans)
  {
    if (x == nullptr)
    {
      return;
    }
    process(x->next, ans);
    ans.push_back(x->val);
  }

  vector<int> reversePrint(ListNode *head)
  {
    vector<int> ans;
    process(head, ans);
    return ans;
  }
};

void testReversePrint()
{
  Solution s;
  ListNode *x3 = new ListNode(2);
  ListNode *x2 = new ListNode(3);
  ListNode *x1 = new ListNode(1);
  x1->next = x2;
  x2->next = x3;
  vector<int> o = {2, 3, 1};
  EXPECT_TRUE(o == s.reversePrint(x1));
  EXPECT_SUMMARY;
}

int main()
{
  testReversePrint();
  return 0;
}
