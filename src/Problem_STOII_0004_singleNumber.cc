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
        num = static_cast<unsigned int>(num) >> 1;
      }
    }
    int ans = 0;
    for (int i = 31; i >= 0; i--)
    {
      ans <<= 1;
      ans += cnt[i] % 3;
    }
    return ans;
  }
};
