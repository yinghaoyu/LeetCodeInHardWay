#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minSubArrayLen(int target, vector<int> &nums)
  {
    int n = nums.size();
    vector<int> pre(n + 1);
    for (int i = 0; i < n; i++)
    {
      pre[i + 1] = pre[i] + nums[i];
    }
    int l = 0;
    int r = 1;
    int ans = INT32_MAX;
    while (l < r && r < n)
    {
      while (r < n && pre[r] - pre[l] < target)
      {
        r++;
      }
      while (l < r && pre[r] - pre[l] >= target)
      {
        ans = std::min(ans, r - l);
        l++;
      }
    }
    return ans == INT32_MAX ? 0 : ans;
  }
};

void testMinSubArrayLen()
{
  Solution s;
  vector<int> n1 = {2, 3, 1, 2, 4, 3};
  vector<int> n2 = {1, 4, 4};
  vector<int> n3 = {1, 1, 1, 1, 1, 1, 1, 1};
  EXPECT_EQ_INT(2, s.minSubArrayLen(7, n1));
  EXPECT_EQ_INT(1, s.minSubArrayLen(4, n2));
  EXPECT_EQ_INT(0, s.minSubArrayLen(11, n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMinSubArrayLen();
  return 0;
}
