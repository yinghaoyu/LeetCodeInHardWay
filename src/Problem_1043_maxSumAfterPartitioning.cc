#include <functional>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力递归
  int maxSumAfterPartitioning1(vector<int> &arr, int k)
  {
    int n = arr.size();
    std::function<int(int)> dfs = [&](int i) -> int {
      int ans = 0;
      int max = 0;
      for (int j = i; i - k < j && j >= 0; j--)
      {
        // 一边枚举 j，一边计算子数组的最大值
        max = std::max(max, arr[j]);
        // arr[j...i] 共 i - j + 1 个元素
        ans = std::max(ans, dfs(j - 1) + (i - j + 1) * max);
      }
      return ans;
    };
    return dfs(n - 1);
  }

  // 记忆化搜索
  int maxSumAfterPartitioning2(vector<int> &arr, int k)
  {
    int n = arr.size();
    vector<int> records(n, -1);
    std::function<int(int)> dfs = [&](int i) -> int {
      if (i < 0)
      {
        return 0;
      }
      int &ans = records[i];
      if (ans != -1)
      {
        return ans;
      }
      int max = 0;
      for (int j = i; i - k < j && j >= 0; j--)
      {
        // 一边枚举 j，一边计算子数组的最大值
        max = std::max(max, arr[j]);
        // arr[j...i] 共 i - j + 1 个元素
        ans = std::max(ans, dfs(j - 1) + (i - j + 1) * max);
      }
      return ans;
    };
    return dfs(n - 1);
  }

  // 递归改动态规划
  int maxSumAfterPartitioning3(vector<int> &arr, int k)
  {
    int n = arr.size();
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
      int max = 0;
      for (int j = i; j > i - k && j >= 0; j--)  // 注意这里的 j 要能取到 0 ，否则会遗漏 arr[0]
      {
        max = std::max(max, arr[j]);
        // dp[i+1] 对应的 arr 区间是 arr[0...i] 长度为 i + 1
        dp[i + 1] = std::max(dp[i + 1], dp[j] + (i - j + 1) * max);
      }
    }
    return dp[n];
  }

  // int maxSumAfterPartitioning3(vector<int> &arr, int k)
  // {
  //   int n = arr.size();
  //   vector<int> dp(n + 1);
  //   dp[0] = 0;
  //   for (int i = 1; i < n + 1; i++)  // 从 1 开始，这里没问题
  //   {
  //     int max = 0;
  //     for (int j = i; j > i - k && j > 0; j--) // 但这里是错误的，明显漏掉了 arr[0]
  //     {
  //        max = std::max(max, arr[j]);
  //        dp[i] = std::max(dp[i], dp[j - 1] + (i - j + 1) * max);  // j > 0 保证 j - 1 >= 0
  ///      }
  // }
  // return dp[n];
  // }
};

void testMaxSumAfterPartitioning()
{
  Solution s;
  vector<int> n1 = {1, 15, 7, 9, 2, 5, 10};
  vector<int> n2 = {1, 4, 1, 5, 7, 3, 6, 1, 9, 9, 3};
  vector<int> n3 = {1};
  EXPECT_EQ_INT(84, s.maxSumAfterPartitioning1(n1, 3));
  EXPECT_EQ_INT(83, s.maxSumAfterPartitioning1(n2, 4));
  EXPECT_EQ_INT(1, s.maxSumAfterPartitioning1(n3, 1));
  EXPECT_EQ_INT(84, s.maxSumAfterPartitioning2(n1, 3));
  EXPECT_EQ_INT(83, s.maxSumAfterPartitioning2(n2, 4));
  EXPECT_EQ_INT(1, s.maxSumAfterPartitioning2(n3, 1));
  EXPECT_EQ_INT(84, s.maxSumAfterPartitioning3(n1, 3));
  EXPECT_EQ_INT(83, s.maxSumAfterPartitioning3(n2, 4));
  EXPECT_EQ_INT(1, s.maxSumAfterPartitioning3(n3, 1));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxSumAfterPartitioning();
  return 0;
}
