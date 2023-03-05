#include <deque>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> maxSlidingWindow(vector<int> &nums, int k)
  {
    if (k < 1 || nums.size() < k)
    {
      return {};
    }
    vector<int> ans(nums.size() - k + 1);
    deque<int> q;
    int index = 0;
    for (int r = 0; r < nums.size(); r++)
    {
      while (!q.empty() && nums[q.back()] <= nums[r])
      {
        // 单调递减队列
        q.pop_back();
      }
      q.push_back(r);
      if (q.front() < r - k + 1)
      {
        // 队头节点需要在窗口[r - k + 1, r]内
        // 窗口维持大小为k
        q.pop_front();
      }
      if (r >= k - 1)
      {
        // 从窗口长度第一次符合时开始计算
        ans[index++] = nums[q.front()];
      }
    }
    return ans;
  }
};

void testMaxSlidingWindow()
{
  Solution s;
  vector<int> n1 = {1, 3, -1, -3, 5, 3, 6, 7};
  vector<int> n2 = {1};
  vector<int> o1 = {3, 3, 5, 5, 6, 7};
  vector<int> o2 = {1};
  EXPECT_TRUE(o1 == s.maxSlidingWindow(n1, 3));
  EXPECT_TRUE(o2 == s.maxSlidingWindow(n2, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxSlidingWindow();
  return 0;
}
