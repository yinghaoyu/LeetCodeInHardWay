#include <functional>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 模拟，时间复杂度较大
  int nthUglyNumber(int n)
  {
    vector<int> uglys = {2, 3, 5};
    priority_queue<long, vector<long>, std::greater<long>> que;
    unordered_set<long> seen;
    que.push(1L);
    seen.emplace(1L);
    int ans = 1;
    while (n-- && !que.empty())
    {
      long cur = que.top();
      que.pop();
      ans = static_cast<int>(cur);
      for (auto &ugly : uglys)
      {
        int next = cur * ugly;
        if (seen.find(next) == seen.end())
        {
          que.push(next);
          seen.emplace(next);
        }
      }
    }
    return ans;
  }

  int dp(int n)
  {
    vector<int> dp(n + 1);
    dp[1] = 1;
    int p2 = 1;
    int p3 = 1;
    int p5 = 1;
    for (int i = 2; i <= n; i++)
    {
      int num2 = dp[p2] * 2;
      int num3 = dp[p3] * 3;
      int num5 = dp[p5] * 5;
      dp[i] = std::min(std::min(num2, num3), num5);
      if (dp[i] == num2)
      {
        p2++;
      }
      if (dp[i] == num3)
      {
        p3++;
      }
      if (dp[i] == num5)
      {
        p5++;
      }
    }
    return dp[n];
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(12, s.nthUglyNumber(10));
  EXPECT_EQ_INT(12, s.dp(10));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
