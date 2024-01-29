#include <deque>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxSubarraySumCircular1(vector<int>& nums)
  {
    int n = nums.size();
    // leftMax[i] 表示必须以arr[0]开始， [0, i] 区间内的最大子数组和
    vector<int> leftMax(n);
    leftMax[0] = nums[0];
    int leftSum = nums[0];
    // pre 则表示的是必须以 arr[i] 为结尾的最大子数组和
    int pre = nums[0];
    int ans = nums[0];
    for (int i = 1; i < n; i++)
    {
      pre = std::max(pre + nums[i], nums[i]);
      ans = std::max(ans, pre);
      leftSum += nums[i];
      leftMax[i] = std::max(leftMax[i - 1], leftSum);
    }

    int rightSum = 0;
    for (int i = n - 1; i > 0; i--)
    {
      // 固定右侧的区间，在左区间找最大的子数组和
      rightSum += nums[i];
      ans = std::max(ans, rightSum + leftMax[i - 1]);
    }
    return ans;
  }

  int maxSubarraySumCircular2(vector<int>& nums)
  {
    int n = nums.size();
    // preMax 表示必须以 nums[i] 为结尾子数组的最大值
    int preMax = nums[0];
    int max = nums[0];
    // preMin 表示必须以 nums[i] 为结尾子数组的最小值
    int preMin = nums[0];
    int min = nums[0];
    int sum = nums[0];
    for (int i = 1; i < n; i++)
    {
      preMax = std::max(preMax + nums[i], nums[i]);
      max = std::max(max, preMax);
      preMin = std::min(preMin + nums[i], nums[i]);
      min = std::min(min, preMin);
      sum += nums[i];
    }

    // 如果 max < 0，数组中不包含大于等于 0 的元素，
    // min 将包括数组中的所有元素，导致我们实际取到的子数组为空
    return max > 0 ? std::max(max, sum - min) : max;
  }

  int maxSubarraySumCircular3(vector<int>& nums)
  {
    int n = nums.size();
    deque<pair<int, int>> q;
    int pre = nums[0];
    int ans = nums[0];
    q.push_back({0, pre});
    // 数组延长一倍，延长的部分用原数组填充
    for (int i = 1; i < 2 * n; i++)
    {
      while (!q.empty() && q.front().first < i - n)
      {
        // 队列 [j ... i]
        // 保证队列的长度不超过 n ，即 i - j <= n
        q.pop_front();
      }
      // 前缀和
      pre += nums[i % n];
      // 统计 [j,i] 区间和的最大值
      ans = std::max(ans, pre - q.front().second);
      // TODO: 下面的 while 删掉为什么会出错？
      while (!q.empty() && q.back().second >= pre)
      {
        q.pop_back();
      }
      q.push_back({i, pre});
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, -2, 3, -2};
  vector<int> n2 = {5, -3, 5};
  EXPECT_EQ_INT(3, s.maxSubarraySumCircular1(n1));
  EXPECT_EQ_INT(10, s.maxSubarraySumCircular1(n2));
  EXPECT_EQ_INT(3, s.maxSubarraySumCircular2(n1));
  EXPECT_EQ_INT(10, s.maxSubarraySumCircular2(n2));
  EXPECT_EQ_INT(3, s.maxSubarraySumCircular3(n1));
  EXPECT_EQ_INT(10, s.maxSubarraySumCircular3(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
