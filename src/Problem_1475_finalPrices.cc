#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> finalPrices(vector<int> &prices)
  {
    vector<int> stack;
    vector<int> ans(prices.size());
    for (int i = 0; i < prices.size(); i++)
    {
      // 单调栈
      while (!stack.empty() && prices[stack.back()] >= prices[i])
      {
        ans[stack.back()] = prices[stack.back()] - prices[i];
        stack.pop_back();
      }
      stack.push_back(i);
      ans[i] = prices[i];
    }
    return ans;
  }
};

bool isVectorEqual(vector<int> lhs, vector<int> rhs)
{
  if (lhs.size() != rhs.size())
  {
    return false;
  }
  for (int i = 0; i < lhs.size(); i++)
  {
    if (lhs[i] != rhs[i])
    {
      return false;
    }
  }
  return true;
}

void testFinalPrices()
{
  Solution s;
  vector<int> prices1 = {8, 4, 6, 2, 3};
  vector<int> fin1 = {4, 2, 4, 2, 3};

  vector<int> prices2 = {1, 2, 3, 4, 5};
  vector<int> fin2 = {1, 2, 3, 4, 5};

  vector<int> prices3 = {10, 1, 1, 6};
  vector<int> fin3 = {9, 0, 1, 6};
  EXPECT_TRUE(isVectorEqual(s.finalPrices(prices1), fin1));
  EXPECT_TRUE(isVectorEqual(s.finalPrices(prices2), fin2));
  EXPECT_TRUE(isVectorEqual(s.finalPrices(prices3), fin3));
  EXPECT_SUMMARY;
}

int main()
{
  testFinalPrices();
  return 0;
}
