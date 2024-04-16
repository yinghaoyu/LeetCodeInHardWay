#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

//@sa https://www.bilibili.com/video/BV1NN41137jF/
class Solution
{
 public:
  int f(vector<int>& nums, int index, int rest, unordered_map<int, unordered_map<int, int>>& map)
  {
    if (map.count(index) && map.at(index).count(rest))
    {
      return map.at(index).at(rest);
    }
    if (index == nums.size())
    {
      return rest == 0;
    }
    int p1 = f(nums, index + 1, rest + nums[index], map);
    int p2 = f(nums, index + 1, rest - nums[index], map);
    map[index][rest] = p1 + p2;
    return map.at(index).at(rest);
  }

  // 递归 + 记忆化搜索
  int findTargetSumWays1(vector<int>& nums, int target)
  {
    // 有可能是负数，所以不用数组，用 hash map
    unordered_map<int, unordered_map<int, int>> map;
    return f(nums, 0, target, map);
  }

  // 普通尝试
  // 严格位置依赖的动态规划
  // 平移技巧
  int findTargetSumWays2(vector<int>& nums, int target)
  {
    int sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    if (target < -sum || target > sum)
    {
      return 0;
    }
    int n = nums.size();
    // -sum ~ +sum -> 2 * sum + 1
    int m = 2 * sum + 1;
    // 原本的dp[i][j]含义:
    // nums[0...i-1]范围上，已经形成的累加和是sum
    // nums[i...]范围上，每个数字可以标记+或者-
    // 最终形成累加和为target的不同表达式数目
    // 因为sum可能为负数，为了下标不出现负数，
    // "原本的dp[i][j]"由dp表中的dp[i][j + sum]来表示
    // 也就是平移操作！
    // 一切"原本的dp[i][j]"一律平移到dp表中的dp[i][j + sum]
    vector<vector<int>> dp(n + 1, vector<int>(m));
    // 原本的dp[n][target] = 1，平移！
    dp[n][target + sum] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = -sum; j <= sum; j++)
      {
        if (j + nums[i] + sum < m)
        {
          // 原本是 : dp[i][j] = dp[i + 1][j + nums[i]]
          // 平移！
          dp[i][j + sum] = dp[i + 1][j + nums[i] + sum];
        }
        if (j - nums[i] + sum >= 0)
        {
          // 原本是 : dp[i][j] += dp[i + 1][j - nums[i]]
          // 平移！
          dp[i][j + sum] += dp[i + 1][j - nums[i] + sum];
        }
      }
    }
    // 原本应该返回dp[0][0]
    // 平移！
    // 返回dp[0][0 + sum]
    return dp[0][sum];
  }

  // 优化点一 :
  // 你可以认为arr中都是非负数
  // 因为即便是arr中有负数，比如[3,-4,2]
  // 因为你能在每个数前面用+或者-号
  // 所以[3,-4,2]其实和[3,4,2]达成一样的效果
  // 那么我们就全把arr变成非负数，不会影响结果的
  // 优化点二 :
  // 如果arr都是非负数，并且所有数的累加和是sum
  // 那么如果target<sum，很明显没有任何方法可以达到target，可以直接返回0
  // 优化点三 :
  // arr内部的数组，不管怎么+和-，最终的结果都一定不会改变奇偶性
  // 所以，如果所有数的累加和是sum，
  // 并且与target的奇偶性不一样，没有任何方法可以达到target，可以直接返回0
  // 优化点四 :
  // 比如说给定一个数组, arr = [1, 2, 3, 4, 5] 并且 target = 3
  // 其中一个方案是 : +1 -2 +3 -4 +5 = 3
  // 该方案中取了正的集合为P = {1，3，5}
  // 该方案中取了负的集合为N = {2，4}
  // 所以任何一种方案，都一定有 sum(P) - sum(N) = target
  // 现在我们来处理一下这个等式，把左右两边都加上sum(P) + sum(N)，那么就会变成如下：
  // sum(P) - sum(N) + sum(P) + sum(N) = target + sum(P) + sum(N)
  // 2 * sum(P) = target + 数组所有数的累加和
  // sum(P) = (target + 数组所有数的累加和) / 2
  // 也就是说，任何一个集合，只要累加和是(target + 数组所有数的累加和) / 2
  // 那么就一定对应一种target的方式
  // 也就是说，比如非负数组arr，target = 7, 而所有数累加和是11
  // 求有多少方法组成7，其实就是求有多少种达到累加和(7+11)/2=9的方法
  // 优化点四最重要，把题意转化成 01背包问题
  // 优化点五 :
  // 二维动态规划的空间压缩技巧
  int findTargetSumWays3(vector<int>& arr, int s)
  {
    int sum = 0;
    for (int n : arr)
    {
      sum += n;
    }
    return sum < s || ((s & 1) ^ (sum & 1)) != 0 ? 0 : subset(arr, (s + sum) >> 1);
  }

  // 求非负数组nums有多少个子序列累加和是s
  // 01背包问题(子集累加和严格是t) + 空间压缩
  // dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i]]
  int subset(vector<int>& nums, int s)
  {
    // dp[i]的含义为：任取数组内的元素，和为i的子集数
    vector<int> dp(s + 1);
    dp[0] = 1;
    for (int n : nums)
    {
      for (int i = s; i >= n; i--)
      {
        // 如果i >= n，那么可以选n这个数，方法数 + dp[i-n]
        dp[i] += dp[i - n];
      }
      // 如果 i < n，那么不可选n
    }
    return dp[s];
  }
};

void testFindTargetSumWays()
{
  Solution s;
  vector<int> n1 = {1, 1, 1, 1, 1};
  vector<int> n2 = {1};
  EXPECT_EQ_INT(5, s.findTargetSumWays1(n1, 3));
  EXPECT_EQ_INT(1, s.findTargetSumWays1(n2, 1));
  EXPECT_EQ_INT(5, s.findTargetSumWays2(n1, 3));
  EXPECT_EQ_INT(1, s.findTargetSumWays2(n2, 1));
  EXPECT_EQ_INT(5, s.findTargetSumWays3(n1, 3));
  EXPECT_EQ_INT(1, s.findTargetSumWays3(n2, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testFindTargetSumWays();
  return 0;
}
