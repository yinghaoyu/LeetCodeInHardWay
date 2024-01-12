#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int subarraysWithKDistinct(vector<int>& nums, int k) { return numsOfMostKinds(nums, k) - numsOfMostKinds(nums, k - 1); }

  // arr中有多少子数组，数字种类不超过k
  // arr的长度是n，arr里的数值1~n之间
  int numsOfMostKinds(vector<int>& arr, int k)
  {
    vector<int> cnt(2e4 + 1);
    int ans = 0;
    for (int l = 0, r = 0, collect = 0; r < arr.size(); r++)
    {
      // r(刚进)
      if (++cnt[arr[r]] == 1)
      {
        collect++;
      }
      // l .. r 要求不超过3种，已经4种，l往右(吐数字)
      while (collect > k)
      {
        if (--cnt[arr[l++]] == 0)
        {
          collect--;
        }
      }
      // l.....r不超过了
      // 0...3
      // 0~3
      // 1~3
      // 2~3
      // 3~3
      ans += r - l + 1;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, 2, 1, 2, 3};
  vector<int> n2 = {1, 2, 1, 3, 4};
  EXPECT_EQ_INT(7, s.subarraysWithKDistinct(n1, 2));
  EXPECT_EQ_INT(3, s.subarraysWithKDistinct(n2, 3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
