#include <iostream>
#include <numeric>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minElements(vector<int> &nums, int limit, int goal)
  {
    long long sum = std::accumulate(nums.begin(), nums.end(), 0ll);
    long long diff = std::abs(goal - sum);
    return (diff + limit - 1) / limit;
  }
};

void testMinElements()
{
  Solution s;
  vector<int> n1 = {1, -1, 1};
  vector<int> n2 = {1, -10, 9, 1};
  EXPECT_EQ_INT(2, s.minElements(n1, 3, -4));
  EXPECT_EQ_INT(1, s.minElements(n2, 100, 0));
  EXPECT_SUMMARY;
}

int main()
{
  testMinElements();
  return 0;
}
