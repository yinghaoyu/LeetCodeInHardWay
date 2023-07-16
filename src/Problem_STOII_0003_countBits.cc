#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0338 相同
// https://leetcode-cn.com/problems/counting-bits/
// see at Problem_0338_countBits.cc
class Solution
{
 public:
  int bitCount(int x)
  {
    int n = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    n = (n & 0x33333333) + ((n >> 2) & 0x33333333);
    n = (n & 0x0f0f0f0f) + ((n >> 4) & 0x0f0f0f0f);
    n = (n & 0x00ff00ff) + ((n >> 8) & 0x00ff000ff);
    n = (n & 0x0000ffff) + ((n >> 16) & 0x0000ffff);
    return n;
  }

  vector<int> countBits(int n)
  {
    vector<int> ans;
    ans.reserve(n + 1);
    for (int i = 0; i <= n; i++)
    {
      ans.push_back(bitCount(i));
    }
    return ans;
  }
};
