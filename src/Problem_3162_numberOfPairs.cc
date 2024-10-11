#include <vector>

using namespace std;

class Solution
{
 public:
  // 暴力枚举
  // 倍数枚举见 Problem_3164_numberOfPairs.cc
  int numberOfPairs(vector<int>& nums1, vector<int>& nums2, int k)
  {
    int ans = 0;
    for (int a : nums1)
    {
      for (int b : nums2)
      {
        if (a % (b * k) == 0)
        {
          ans++;
        }
      }
    }
    return ans;
  }
};
