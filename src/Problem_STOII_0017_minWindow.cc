#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 0076 相同
// https://leetcode-cn.com/problems/minimum-window-substring/
// see at Problem_0076_minWindow.cc
class Solution
{
 public:
  string minWindow(string s, string t)
  {
    int n = s.length();
    int m = t.length();
    vector<int> cnt(256);
    for (auto &c : t)
    {
      cnt[c]++;
    }
    int left = 0;
    int right = 0;
    int all = m;
    int len = -1;
    int lpos = -1;
    int rpos = -1;
    while (right < n)
    {
      cnt[s[right]]--;
      if (cnt[s[right]] >= 0)
      {
        all--;
      }
      if (0 == all)
      {
        while (cnt[s[left]] < 0)
        {
          cnt[s[left]]++;
          left++;
        }
        if (len == -1 || len > right - left + 1)
        {
          len = right - left + 1;
          lpos = left;
          rpos = right;
        }
        all++;
        cnt[s[left]]++;
        left++;
      }
      right++;
    }
    return len == -1 ? "" : s.substr(lpos, len);
  }
};
