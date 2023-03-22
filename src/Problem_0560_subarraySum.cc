#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int subarraySum(vector<int> &nums, int k)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    unordered_map<int, int> map;
    // 为了让每个单独的元素可以满足条件
    map.emplace(0, 1);
    int all = 0;
    int ans = 0;
    for (int i = 0; i < nums.size(); i++)
    {
      all += nums[i];  // 0...i的前缀和
      if (map.count(all - k))
      {
        ans += map.at(all - k);
      }
      if (!map.count(all))
      {
        map.emplace(all, 1);
      }
      else
      {
        map[all]++;
      }
    }
    return ans;
  }
};

void testSubArraySum()
{
  Solution s;
  vector<int> n1 = {1, 1, 1};
  vector<int> n2 = {1, 2, 3};
  EXPECT_EQ_INT(2, s.subarraySum(n1, 2));
  EXPECT_EQ_INT(2, s.subarraySum(n2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testSubArraySum();
  return 0;
}
