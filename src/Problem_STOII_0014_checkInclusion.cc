#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0567 相同
// https://leetcode.cn/problems/permutation-in-string/
// see at Problem_0567_checkInclusion.cc
class Solution
{
 public:
  bool checkInclusion(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    vector<int> cnt(26);
    for (auto &c : s1)
    {
      cnt[c - 'a']--;
    }
    int left = 0;
    int right = 0;
    while (right < m)
    {
      int x = s2[right] - 'a';
      cnt[x]++;
      while (cnt[x] > 0)
      {
        cnt[s2[left] - 'a']--;
        left++;
      }
      if (right - left + 1 == n)
      {
        return true;
      }
      right++;
    }
    return false;
  }
};
