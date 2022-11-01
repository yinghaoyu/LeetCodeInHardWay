#include <algorithm>
#include <iostream>  // for_each
#include <numeric>   // accumulate
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool arrayStringsAreEqual1(vector<string> &word1, vector<string> &word2)
  {
    auto p1 = std::accumulate(word1.begin(), word1.end(), string(""), [](string &s1, string &s2) { return s1 + s2; });
    auto p2 = std::accumulate(word2.begin(), word2.end(), string(""), [](string &s1, string &s2) { return s1 + s2; });
    return p1 == p2;
  }

  bool arrayStringsAreEqual2(vector<string> &word1, vector<string> &word2)
  {
    string p3;
    string p4;
    std::for_each(word1.begin(), word1.end(), [&](const string &s) { p3 += s; });
    std::for_each(word2.begin(), word2.end(), [&](const string &s) { p4 += s; });
    return p3 == p4;
  }

  bool arrayStringsAreEqual3(vector<string> &word1, vector<string> &word2)
  {
    int i = 0;
    int j = 0;
    int p = 0;
    int q = 0;
    int n = word1.size();
    int m = word2.size();
    while (i < n && j < m)
    {
      if (word1[i][p++] != word2[j][q++])
      {
        return false;
      }
      if (p == word1[i].length())
      {
        i++;
        p = 0;
      }
      if (q == word2[j].length())
      {
        j++;
        q = 0;
      }
    }
    return i == n && j == m;
  }
};

void testArrayStringsAreEqual()
{
  Solution s;
  vector<string> n1 = {"ab", "c"};
  vector<string> n2 = {"a", "bc"};
  vector<string> n3 = {"a", "cb"};
  vector<string> n4 = {"ab", "c"};
  vector<string> n5 = {"abc", "d", "defg"};
  vector<string> n6 = {"abcddefg"};
  EXPECT_TRUE(s.arrayStringsAreEqual1(n1, n2));
  EXPECT_FALSE(s.arrayStringsAreEqual1(n3, n4));
  EXPECT_TRUE(s.arrayStringsAreEqual1(n5, n6));
  EXPECT_TRUE(s.arrayStringsAreEqual2(n1, n2));
  EXPECT_FALSE(s.arrayStringsAreEqual2(n3, n4));
  EXPECT_TRUE(s.arrayStringsAreEqual2(n5, n6));
  EXPECT_TRUE(s.arrayStringsAreEqual3(n1, n2));
  EXPECT_FALSE(s.arrayStringsAreEqual3(n3, n4));
  EXPECT_TRUE(s.arrayStringsAreEqual3(n5, n6));
  EXPECT_SUMMARY;
}

int main()
{
  testArrayStringsAreEqual();
  return 0;
}
