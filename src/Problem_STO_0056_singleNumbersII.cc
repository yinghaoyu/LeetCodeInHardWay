#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int singleNumber(vector<int> &nums)
  {
    vector<int> cnt(32);
    for (auto &num : nums)
    {
      for (int i = 0; i < 32; i++)
      {
        cnt[i] += num & 1;
        num = static_cast<uint>(num >> 1);
      }
    }
    int ans = 0;
    int m = 3;
    for (int i = 31; i >= 0; i--)
    {
      ans <<= 1;
      ans += cnt[i] % 3;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {3, 4, 3, 3};
  vector<int> n2 = {9, 1, 7, 9, 7, 9, 7};
  EXPECT_EQ_INT(4, s.singleNumber(n1));
  EXPECT_EQ_INT(1, s.singleNumber(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
