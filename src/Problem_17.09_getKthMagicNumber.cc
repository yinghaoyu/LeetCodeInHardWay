#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getKthMagicNumber1(int k)
  {
    vector<int> factors = {3, 5, 7};
    unordered_set<long> seen;
    priority_queue<long, vector<long>, greater<long>> heap;
    seen.insert(1L);
    heap.push(1L);
    int magic = 0;
    for (int i = 0; i < k; i++)  // 时间复杂度 k * log(k)
    {
      long curr = heap.top();
      heap.pop();
      magic = (int) curr;
      for (int factor : factors)
      {
        long next = curr * factor;
        if (!seen.count(next))  // 去重
        {
          seen.insert(next);
          heap.push(next);
        }
      }
    }
    return magic;
  }

  // 动态规划
  int getKthMagicNumber2(int k)
  {
    vector<int> dp(k + 1);
    dp[1] = 1;
    int p3 = 1, p5 = 1, p7 = 1;
    for (int i = 2; i <= k; i++)
    {
      int num3 = dp[p3] * 3, num5 = dp[p5] * 5, num7 = dp[p7] * 7;
      dp[i] = std::min(std::min(num3, num5), num7);
      if (dp[i] == num3)
      {
        p3++;
      }
      if (dp[i] == num5)
      {
        p5++;
      }
      if (dp[i] == num7)
      {
        p7++;
      }
    }
    return dp[k];
  }
};

void testGetKthMagicNumber()
{
  Solution s;
  EXPECT_EQ_INT(5, s.getKthMagicNumber1(3));
  EXPECT_EQ_INT(7, s.getKthMagicNumber1(4));
  EXPECT_EQ_INT(9, s.getKthMagicNumber1(5));
  EXPECT_EQ_INT(15, s.getKthMagicNumber1(6));
  EXPECT_EQ_INT(21, s.getKthMagicNumber1(7));

  EXPECT_EQ_INT(5, s.getKthMagicNumber2(3));
  EXPECT_EQ_INT(7, s.getKthMagicNumber2(4));
  EXPECT_EQ_INT(9, s.getKthMagicNumber2(5));
  EXPECT_EQ_INT(15, s.getKthMagicNumber2(6));
  EXPECT_EQ_INT(21, s.getKthMagicNumber2(7));
  EXPECT_SUMMARY;
}

int main()
{
  testGetKthMagicNumber();
  return 0;
}
