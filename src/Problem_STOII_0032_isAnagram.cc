#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0242
// https://leetcode-cn.com/problems/valid-anagram/
// Problem_0242_isAnagram.cc
class Solution
{
 public:
  bool isAnagram(string s, string t)
  {
    if (s.length() != t.length())
    {
      return false;
    }
    vector<int> cnt(256);
    for (auto &c : s)
    {
      cnt[c]++;
    }
    for (auto &c : t)
    {
      if (--cnt[c] < 0)
      {
        return false;
      }
    }
    return true;
  }
};
