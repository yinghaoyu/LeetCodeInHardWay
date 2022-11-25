#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool expand(string &s1, string &s2)
  {
    int i = 0;
    int j = 0;
    int n = s1.length();
    int m = s2.length();
    while (i < n && j < m)
    {
      if (s1[i] != s2[j])
      {
        return false;
      }
      char c = s1[i];
      int p1 = 0;
      while (i < n && s1[i] == c)
      {
        p1++;
        i++;
      }
      int p2 = 0;
      while (j < m && s2[j] == c)
      {
        p2++;
        j++;
      }
      if (p1 < p2)
      {
        return false;
      }
      if (p1 != p2 && p1 < 3)
      {
        return false;
      }
    }
    return i == n && j == m;  // 同时遍历完
  }

  int expressiveWords(string s, vector<string> &words)
  {
    int ans = 0;
    for (auto &word : words)
    {
      if (expand(s, word))
      {
        ans++;
      }
    }
    return ans;
  }
};

void testExpressiveWords()
{
  Solution s;
  vector<string> w1 = {"hello", "hi", "helo"};
  vector<string> w2 = {"zzyy", "zy", "zyy"};
  EXPECT_EQ_INT(1, s.expressiveWords("heeellooo", w1));
  EXPECT_EQ_INT(3, s.expressiveWords("zzzzzyyyyy", w2));
  EXPECT_SUMMARY;
}

int main()
{
  testExpressiveWords();
  return 0;
}
