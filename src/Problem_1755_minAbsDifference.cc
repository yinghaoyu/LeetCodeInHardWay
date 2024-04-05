#include <algorithm>
#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV11w411y79P/ Code03
// 由于 -1e7 <= num[i] <= 1e7，动态规划开辟不了这么大的数组空间
// 同时全量样本递归展开超时，这时候就需要双向广搜解决
class Solution
{
 public:
  // 双向广搜
  int minAbsDifference(vector<int>& nums, int goal)
  {
    int n = nums.size();
    // 负数和
    long min = 0;
    // 非负数和
    long max = 0;
    for (int i = 0; i < n; i++)
    {
      if (nums[i] >= 0)
      {
        max += nums[i];
      }
      else
      {
        min += nums[i];
      }
    }
    // 剪枝
    if (max < goal)
    {
      return std::abs(max - goal);
    }
    if (min > goal)
    {
      return std::abs(min - goal);
    }
    // 原始数组排序，为了后面递归的时候剪枝
    // 常数优化
    std::sort(nums.begin(), nums.end());
    vector<int> lsum;
    vector<int> rsum;
    // 左部分展开
    collect(nums, 0, n >> 1, 0, lsum);
    // 右部分展开
    collect(nums, n >> 1, n, 0, rsum);
    std::sort(lsum.begin(), lsum.end());
    std::sort(rsum.begin(), rsum.end());
    int ans = std::abs(goal);
    // 滑动窗口
    for (int i = 0, j = rsum.size() - 1; i < lsum.size(); i++)
    {
      while (j > 0 && std::abs(goal - lsum[i] - rsum[j - 1]) <= std::abs(goal - lsum[i] - rsum[j]))
      {
        // 如果滑动后值更小
        j--;
      }
      ans = std::min(ans, std::abs(goal - lsum[i] - rsum[j]));
    }
    return ans;
  }

  void collect(vector<int>& nums, int i, int e, int s, vector<int>& sum)
  {
    if (i == e)
    {
      sum.push_back(s);
    }
    else
    {
      // 前面对 nums 数组排序的作用，在这里剪枝
      // nums[i.....]这一组，相同的数字有几个
      int j = i + 1;
      while (j < e && nums[j] == nums[i])
      {
        j++;
      }
      // nums[ 1 1 1 1 1 2....
      //       i         j
      // 这个 for 循环比二叉展开快
      for (int k = 0; k <= j - i; k++)
      {
        // k = 0个
        // k = 1个
        // k = 2个
        collect(nums, j, e, s + k * nums[i], sum);
      }
    }
  }
};
