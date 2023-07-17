#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 438 相同
// https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/
// see at Problem_0438_findAnagrams.cc
class Solution
{
 public:
  vector<int> findAnagrams(string s, string p)
  {
    vector<int> cnt(26);
    for (auto &c : p)
    {
      cnt[c - 'a']--;
    }
    int left = 0;
    int right = 0;
    int n = s.length();
    int m = p.length();
    vector<int> ans;
    while (right < n)
    {
      int x = s[right] - 'a';
      cnt[x]++;
      while (cnt[x] > 0)
      {
        cnt[s[left] - 'a']--;
        left++;
      }
      if (right - left + 1 == m)
      {
        ans.push_back(left);
      }
      right++;
    }
    return ans;
  }
};
