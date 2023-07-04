#include <iostream>
#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int matrixSum(vector<vector<int>> &nums)
  {
    int ans = 0;
    int n = nums.size();
    int m = nums[0].size();
    for (int i = 0; i < n; i++)
    {
      std::sort(nums[i].begin(), nums[i].end());
    }
    for (int j = 0; j < m; j++)
    {
      int max = 0;
      for (int i = 0; i < n; i++)
      {
        max = std::max(max, nums[i][j]);
      }
      ans += max;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{7, 2, 1}, {6, 4, 2}, {6, 5, 3}, {3, 2, 1}};
  vector<vector<int>> n2 = {{1}};
  EXPECT_EQ_INT(15, s.matrixSum(n1));
  EXPECT_EQ_INT(1, s.matrixSum(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
