#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int distinctAverages(vector<int> &nums)
  {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    unordered_set<int> sets;
    for (int i = 0, j = n - 1; i < j; i++, j--)
    {
      sets.emplace((nums[i] + nums[j]));
    }
    return sets.size();
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {4, 1, 4, 0, 3, 5};
  vector<int> n2 = {1, 100};
  EXPECT_EQ_INT(2, s.distinctAverages(n1));
  EXPECT_EQ_INT(1, s.distinctAverages(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
