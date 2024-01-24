#include <algorithm>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  int minAbsDifference(vector<int>& nums, int goal)
  {
    int n = nums.size();
    long min = 0;
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
    if (max < goal)
    {
      return std::abs(max - goal);
    }
    if (min > goal)
    {
      return std::abs(min - goal);
    }
    // 原始数组排序，为了后面递归的时候，还能剪枝
    // 常数优化
    std::sort(nums.begin(), nums.end());
    vector<int> lsum;
    vector<int> rsum;
    collect(nums, 0, n >> 1, 0, lsum);
    collect(nums, n >> 1, n, 0, rsum);
    std::sort(lsum.begin(), lsum.end());
    std::sort(rsum.begin(), rsum.end());
    int ans = std::abs(goal);
    for (int i = 0, j = rsum.size() - 1; i < lsum.size(); i++)
    {
      while (j > 0 && std::abs(goal - lsum[i] - rsum[j - 1]) <= std::abs(goal - lsum[i] - rsum[j]))
      {
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
      // nums[i.....]这一组，相同的数字有几个
      int j = i + 1;
      while (j < e && nums[j] == nums[i])
      {
        j++;
      }
      // nums[ 1 1 1 1 1 2....
      //       i         j
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
