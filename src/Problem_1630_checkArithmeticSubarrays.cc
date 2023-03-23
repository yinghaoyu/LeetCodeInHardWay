#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l, vector<int> &r)
  {
    int N = l.size();
    vector<bool> ans;
    for (int i = 0; i < N; i++)
    {
      int left = l[i];
      int right = r[i];
      int min = *min_element(nums.begin() + left, nums.begin() + right + 1);
      int max = *max_element(nums.begin() + left, nums.begin() + right + 1);
      if (min == max)
      {
        // 说明这个子数组所有的值相等
        ans.push_back(true);
        continue;
      }
      if ((max - min) % (right - left) != 0)
      {
        // 子数组的公差 d 不是整数
        ans.push_back(false);
        continue;
      }
      int d = (max - min) / (right - left);
      bool can = true;
      vector<int> seen(right - left + 1);
      for (int j = left; j <= right; j++)
      {
        if ((nums[j] - min) % d != 0)
        {
          // 说明这个数不符合等差数列
          can = false;
          break;
        }
        // 根据公差，计算这个数在子数组的位置
        int t = (nums[j] - min) / d;
        if (seen[t])
        {
          // 重复访问说明出错
          can = false;
          break;
        }
        seen[t] = true;
      }
      ans.push_back(can);
    }
    return ans;
  }
};

void testCheckArithmeticSubarrays()
{
  Solution s;
  vector<int> n1 = {4, 6, 5, 9, 3, 7};
  vector<int> l1 = {0, 0, 2};
  vector<int> r1 = {2, 3, 5};
  vector<bool> o1 = {true, false, true};

  vector<int> n2 = {-12, -9, -3, -12, -6, 15, 20, -25, -20, -15, -10};
  vector<int> l2 = {0, 1, 6, 4, 8, 7};
  vector<int> r2 = {4, 4, 9, 7, 9, 10};
  vector<bool> o2 = {false, true, false, false, true, true};

  EXPECT_TRUE(o1 == s.checkArithmeticSubarrays(n1, l1, r1));
  EXPECT_TRUE(o2 == s.checkArithmeticSubarrays(n2, l2, r2));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckArithmeticSubarrays();
  return 0;
}
