#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class ListNode
{
 public:
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
 public:
  bool cheak(vector<int> &nums, int value)
  {
    for (int i = 0; i < nums.size(); i++)
    {
      if (nums[i] == value)
      {
        return true;
      }
    }
    return false;
  }

  int numComponents(ListNode *head, vector<int> &nums)
  {
    unordered_set<int> sets;
    for (int num : nums)
    {
      // 加快检索
      sets.emplace(num);
    }
    bool cover = false;
    int ans = 0;
    while (head != nullptr)
    {
      // 只需要计算起始位置
      if (sets.count(head->val))
      {
        if (!cover)
        {
          // 第一次
          cover = true;
          ans++;
        }
      }
      else
      {
        cover = false;
      }
      head = head->next;
    }
    return ans;
  }
};

void testNumComponents()
{
  Solution s;

  ListNode *x1 = new ListNode(0);
  ListNode *x2 = new ListNode(1);
  ListNode *x3 = new ListNode(2);
  ListNode *x4 = new ListNode(3);
  x1->next = x2;
  x2->next = x3;
  x3->next = x4;
  vector<int> nums1 = {0, 1, 3};

  ListNode *y1 = new ListNode(0);
  ListNode *y2 = new ListNode(1);
  ListNode *y3 = new ListNode(2);
  ListNode *y4 = new ListNode(3);
  ListNode *y5 = new ListNode(4);
  y1->next = y2;
  y2->next = y3;
  y3->next = y4;
  y4->next = y5;
  vector<int> nums2 = {0, 3, 1, 4};
  EXPECT_EQ_INT(2, s.numComponents(x1, nums1));
  EXPECT_EQ_INT(2, s.numComponents(y1, nums2));
  EXPECT_SUMMARY;
}

int main()
{
  testNumComponents();
  return 0;
}
