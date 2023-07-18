#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0003 相同
// https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/
// see at Problem_0003_lengthOfLongestSubstring.cc
class Solution
{
 public:
  int lengthOfLongestSubstring(string s)
  {
    int n = s.length();
    int left = 0;
    int right = 0;
    vector<int> cnt(256);
    int ans = 0;
    while (right < n)
    {
      int x = s[right];
      cnt[x]++;
      while (cnt[x] > 1)
      {
        cnt[s[left]]--;
        left++;
      }
      ans = std::max(ans, right - left + 1);
      right++;
    }
    return ans;
  }
};
