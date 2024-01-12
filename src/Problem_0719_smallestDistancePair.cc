#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 时间复杂度O(n * log(n) + log(max-min) * n)，额外空间复杂度O(1)
  int smallestDistancePair(vector<int>& nums, int k)
  {
    int n = nums.size();
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    // [0, 最大-最小]，不停二分
    for (int l = 0, r = nums[n - 1] - nums[0], m, cnt; l <= r;)
    {
      // m中点，arr中任意两数的差值 <= m
      m = (r - l) / 2 + l;
      // 返回数字对的数量
      cnt = f(nums, m);
      if (cnt >= k)
      {
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return ans;
  }

  // arr中任意两数的差值 <= limit
  // 这样的数字配对，有几对？
  int f(vector<int>& arr, int limit)
  {
    int ans = 0;
    // O(n)
    for (int l = 0, r = 0; l < arr.size(); l++)
    {
      // l...r r+1
      while (r + 1 < arr.size() && arr[r + 1] - arr[l] <= limit)
      {
        r++;
      }
      // arr[l...r]范围上的数差值的绝对值都不超过limit
      // arr[0...3]
      // 0,1
      // 0,2
      // 0,3
      ans += r - l;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 3, 1};
  vector<int> n2 = {1, 1, 1};
  vector<int> n3 = {1, 6, 1};
  EXPECT_EQ_INT(0, s.smallestDistancePair(n1, 1));
  EXPECT_EQ_INT(0, s.smallestDistancePair(n2, 2));
  EXPECT_EQ_INT(5, s.smallestDistancePair(n3, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
