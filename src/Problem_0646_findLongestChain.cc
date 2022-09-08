#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 动态规划
  // dp[i] 为以 pairs[i] 为结尾的最长数对链的长度
  // 计算 dp[i] 时，可以先找出所有的满足 pairs[i][0] > pairs[j][1] 的 j，并求出最大的 dp[j]
  // dp[i] 的值即可赋为这个最大值加一
  // 这种动态规划的思路要求计算 dp[i] 时，所有潜在的 dp[j] 已经计算完成
  // 可以先将 pairs 进行排序来满足这一要求。初始化时，dp 需要全部赋值为 1
  int findLongestChain1(vector<vector<int>> &pairs)
  {
    int N = pairs.size();
    std::sort(pairs.begin(), pairs.end());
    vector<int> dp(N, 1);
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < i; j++)
      {
        if (pairs[i][0] > pairs[j][1])
        {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    return dp[N - 1];
  }

  // 方法一实际上是「最长递增子序列」的动态规划解法，
  // 这个解法可以改造为贪心 + 二分查找的形式。
  // 用一个数组 arr 来记录当前最优情况，
  // arr[i] 就表示长度为 i+1 的数对链的末尾可以取得的最小值，
  // 遇到一个新数对时，先用二分查找得到这个数对可以放置的位置，再更新 arr。
  int findLongestChain2(vector<vector<int>> &pairs)
  {
    sort(pairs.begin(), pairs.end());
    vector<int> arr;
    for (auto p : pairs)
    {
      int x = p[0], y = p[1];
      if (arr.size() == 0 || x > arr.back())
      {
        arr.emplace_back(y);
      }
      else
      {
        int idx = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        arr[idx] = min(arr[idx], y);
      }
    }
    return arr.size();
  }

  // 贪心：要挑选最长数对链的第一个数对时，
  // 最优的选择是挑选第二个数字最小的，
  // 这样能给挑选后续的数对留下更多的空间
  static bool compare(vector<int> l, vector<int> r) { return l[1] < r[1]; }
  int findLongestChain3(vector<vector<int>> &pairs)
  {
    std::sort(pairs.begin(), pairs.end(), compare);
    int ans = 1;
    int N = pairs.size();
    int start = pairs[0][1];
    for (int j = 1; j < N; j++)
    {
      if (start < pairs[j][0])
      {
        ans++;
        start = pairs[j][1];
      }
    }
    return ans;
  }
};

void testFindLongestChain()
{
  Solution s;

  vector<vector<int>> pairs1 = {{1, 2}, {2, 3}, {3, 4}};
  vector<vector<int>> pairs2 = {{1, 2}, {7, 8}, {4, 5}};
  vector<vector<int>> pairs3 = {{7, 9}, {4, 5}, {7, 9}, {-7, -1}, {0, 10}, {3, 10}, {3, 6}, {2, 3}};
  vector<vector<int>> pairs4 = {{1, 2}};

  EXPECT_EQ_INT(2, s.findLongestChain3(pairs1));
  EXPECT_EQ_INT(3, s.findLongestChain3(pairs2));
  EXPECT_EQ_INT(4, s.findLongestChain3(pairs3));
  EXPECT_EQ_INT(1, s.findLongestChain3(pairs4));

  EXPECT_EQ_INT(s.findLongestChain3(pairs1), s.findLongestChain1(pairs1));
  EXPECT_EQ_INT(s.findLongestChain3(pairs2), s.findLongestChain1(pairs2));
  EXPECT_EQ_INT(s.findLongestChain3(pairs3), s.findLongestChain1(pairs3));
  EXPECT_EQ_INT(s.findLongestChain3(pairs4), s.findLongestChain1(pairs4));

  EXPECT_EQ_INT(s.findLongestChain3(pairs1), s.findLongestChain2(pairs1));
  EXPECT_EQ_INT(s.findLongestChain3(pairs2), s.findLongestChain2(pairs2));
  EXPECT_EQ_INT(s.findLongestChain3(pairs3), s.findLongestChain2(pairs3));
  EXPECT_EQ_INT(s.findLongestChain3(pairs4), s.findLongestChain2(pairs4));
  EXPECT_SUMMARY;
}

int main()
{
  testFindLongestChain();
  return 0;
}
