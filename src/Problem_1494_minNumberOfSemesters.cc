#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  int minNumberOfSemesters(int n, vector<vector<int>> &relations, int k)
  {
    vector<int> dp(1 << n, INT32_MAX);
    vector<int> need(1 << n, 0);
    for (auto &edge : relations)
    {
      need[(1 << (edge[1] - 1))] |= 1 << (edge[0] - 1);
    }
    dp[0] = 0;
    for (int i = 1; i < (1 << n); ++i)
    {
      need[i] = need[i & (i - 1)] | need[i & (-i)];
      if ((need[i] | i) != i)
      {
        // i 中有任意一门课程的前置课程没有完成学习
        continue;
      }
      int valid = i ^ need[i];  // 当前学期可以进行学习的课程集合
      if (__builtin_popcount(valid) <= k)
      {
        // 如果个数小于 k，则可以全部学习，不再枚举子集
        dp[i] = min(dp[i], dp[i ^ valid] + 1);
      }
      else
      {
        // 否则枚举当前学期需要进行学习的课程集合
        for (int sub = valid; sub; sub = (sub - 1) & valid)
        {
          if (__builtin_popcount(sub) <= k)
          {
            dp[i] = min(dp[i], dp[i ^ sub] + 1);
          }
        }
      }
    }
    return dp[(1 << n) - 1];
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{2, 1}, {3, 1}, {1, 4}};
  vector<vector<int>> n2 = {{2, 1}, {3, 1}, {4, 1}, {1, 5}};
  EXPECT_EQ_INT(3, s.minNumberOfSemesters(4, n1, 2));
  EXPECT_EQ_INT(4, s.minNumberOfSemesters(5, n2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
