#include <clocale>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxProfit(vector<int> &prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    // 股价的最小值
    int min = prices[0];
    int ans = 0;
    for (int i = 0; i < prices.size(); i++)
    {
      // 每次遍历找到股价的最小值
      min = std::min(min, prices[i]);
      ans = std::max(ans, prices[i] - min);
    }
    return ans;
  }
};

void testMaxProfit()
{
  Solution s;
  vector<int> p1 = {7, 1, 5, 3, 6, 4};
  vector<int> p2 = {7, 6, 4, 3, 1};
  EXPECT_EQ_INT(5, s.maxProfit(p1));
  EXPECT_EQ_INT(0, s.maxProfit(p2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProfit();
  return 0;
}
