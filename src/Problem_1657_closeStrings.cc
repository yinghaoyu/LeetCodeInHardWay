#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool closeStrings(string word1, string word2)
  {
    if (word1.length() != word2.length())
    {
      return false;
    }
    vector<int> m(26);
    vector<int> n(26);
    for (auto& c : word1)
    {
      m[c - 'a']++;
    }
    for (auto& c : word2)
    {
      n[c - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
      if (m[i] == 0 && n[i] > 0)
      {
        return false;
      }
      if (m[i] > 0 && n[i] == 0)
      {
        return false;
      }
    }
    std::sort(m.begin(), m.end());
    std::sort(n.begin(), n.end());
    return m == n;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE(s.closeStrings("abc", "bca"));
  EXPECT_FALSE(s.closeStrings("a", "aa"));
  EXPECT_TRUE(s.closeStrings("cabbba", "abbccc"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
