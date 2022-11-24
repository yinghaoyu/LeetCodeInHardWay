#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  double champagneTower(int poured, int query_row, int query_glass)
  {
    double dp[101][101] = {0.0};
    // 所有的酒都先装入第一个杯子
    dp[0][0] = poured;
    // 从上到下，从左到右，按层遍历所有杯子
    // 不需要全部计算完，只需要计算到指定位置
    for (int i = 0; i <= query_row; i++)
    {
      // 第i行，就有i个杯子
      for (int j = 0; j <= i; j++)
      {
        if (dp[i][j] >= 1)
        {
          // 剩余的酒
          double remain = dp[i][j] - 1;
          // 这个杯子装满了
          dp[i][j] = 1;
          // 它下面的两个杯子均分剩余的酒
          dp[i + 1][j] += remain / 2;
          dp[i + 1][j + 1] += remain / 2;
        }
      }
    }
    return dp[query_row][query_glass];
  }
};

void testChampagneTower()
{
  Solution s;
  EXPECT_EQ_DOUBLE(0.00000, s.champagneTower(1, 1, 1));
  EXPECT_EQ_DOUBLE(0.50000, s.champagneTower(2, 1, 1));
  EXPECT_EQ_DOUBLE(1.00000, s.champagneTower(100000009, 33, 17));
  EXPECT_SUMMARY;
}

int main()
{
  testChampagneTower();
  return 0;
}
