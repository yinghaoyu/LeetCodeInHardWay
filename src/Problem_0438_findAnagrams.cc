#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> findAnagrams(string s, string p)
  {
    vector<int> ans;
    if (s.length() == 0 || p.length() == 0 || s.length() < p.length())
    {
      return ans;
    }
    int N = s.length();
    int M = p.length();
    unordered_map<char, int> map;
    // 先统计p字符串的字符
    for (auto& c : p)
    {
      if (!map.count(c))
      {
        map.emplace(c, 1);
      }
      else
      {
        map[c]++;
      }
    }
    int all = M;
    // 滑动窗口，如果窗口长度不够，统计消耗的字符数
    for (int end = 0; end < M - 1; end++)
    {
      if (map.count(s[end]))
      {
        int count = map.at(s[end]);
        if (count > 0)
        {
          all--;
        }
        map[s[end]]--;
      }
    }
    // 窗口长度够，就同时往右移动
    for (int end = M - 1, start = 0; end < N; end++, start++)
    {
      if (map.count(s[end]))
      {
        // 右边字符进入
        int count = map.at(s[end]);
        if (count > 0)
        {
          all--;
        }
        map[s[end]]--;
      }
      if (all == 0)
      {
        // 刚好抵消，说明找到了一种答案
        ans.push_back(start);
      }
      if (map.count(s[start]))
      {
        // 左边字符出去
        int count = map.at(s[start]);
        if (count >= 0)
        {
          all++;
        }
        map[s[start]]++;
      }
    }
    return ans;
  }
};

bool isVectorEuqal(vector<int> a, vector<int> b)
{
  std::sort(a.begin(), a.end());
  std::sort(b.begin(), b.end());
  return a == b;
}

void testFindAnagrams()
{
  Solution s;
  vector<int> o1 = {0, 6};
  vector<int> o2 = {0, 1, 2};
  EXPECT_TRUE(isVectorEuqal(o1, s.findAnagrams("cbaebabacd", "abc")));
  EXPECT_TRUE(isVectorEuqal(o2, s.findAnagrams("abab", "ab")));
  EXPECT_SUMMARY;
}

int main()
{
  testFindAnagrams();
  return 0;
}
