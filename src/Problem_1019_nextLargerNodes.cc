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
  vector<int> nextLargerNodes(ListNode *head)
  {
    vector<int> tmp;
    while (head != nullptr)
    {
      tmp.push_back(head->val);
      head = head->next;
    }
    int n = tmp.size();
    vector<int> stack;
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && tmp[stack.back()] < tmp[i])
      {
        int index = stack.back();
        stack.pop_back();
        ans[index] = tmp[i];
      }
      stack.push_back(i);
    }
    return ans;
  }
};

void testNextLargerNodes()
{
  Solution s;
  ListNode *x3 = new ListNode(5, nullptr);
  ListNode *x2 = new ListNode(1, x3);
  ListNode *x1 = new ListNode(2, x2);
  vector<int> o1 = {5, 5, 0};

  ListNode *y5 = new ListNode(5, nullptr);
  ListNode *y4 = new ListNode(3, y5);
  ListNode *y3 = new ListNode(4, y4);
  ListNode *y2 = new ListNode(7, y3);
  ListNode *y1 = new ListNode(2, y2);
  vector<int> o2 = {7, 0, 5, 5, 0};
  EXPECT_TRUE(o1 == s.nextLargerNodes(x1));
  EXPECT_TRUE(o2 == s.nextLargerNodes(y1));
  EXPECT_SUMMARY;
}

int main()
{
  testNextLargerNodes();
  return 0;
}
