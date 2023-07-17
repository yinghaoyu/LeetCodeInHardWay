#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findMaxLength(vector<int> &nums)
  {
    int n = nums.size();
    unordered_map<int, int> map;
    map.emplace(0, -1);
    int sum = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      sum += nums[i] == 1 ? 1 : -1;
      if (map.count(sum))
      {
        ans = std::max(ans, i - map[sum]);
      }
      else
      {
        map[sum] = i;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {0, 1};
  vector<int> n2 = {0, 1, 0};
  EXPECT_EQ_INT(2, s.findMaxLength(n1));
  EXPECT_EQ_INT(2, s.findMaxLength(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
