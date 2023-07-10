#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int threeSumClosest(vector<int> &nums, int target)
  {
    int n = nums.size();
    int ans = 1e9;
    std::sort(nums.begin(), nums.end());

    auto update = [&](int cur)
    {
      if (std::abs(cur - target) < std::abs(ans - target))
      {
        ans = cur;
      }
    };

    for (int i = 0; i < n; i++)
    {
      if (i > 0 && nums[i - 1] == nums[i])
      {
        continue;
      }

      int L = i + 1;
      int R = n - 1;

      while (L < R)
      {
        int sum = nums[i] + nums[L] + nums[R];
        update(sum);
        if (sum < target)
        {
          L++;
        }
        else if (sum > target)
        {
          R--;
        }
        else
        {
          return sum;
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {-1, 2, 1, -4};
  vector<int> n2 = {0, 0, 0};
  EXPECT_EQ_INT(2, s.threeSumClosest(n1, 1));
  EXPECT_EQ_INT(0, s.threeSumClosest(n2, 1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
