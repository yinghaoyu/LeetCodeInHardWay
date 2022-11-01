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
  bool arrayStringsAreEqual(vector<string> &word1, vector<string> &word2)
  {
    auto p1 = std::accumulate(word1.begin(), word1.end(), string(""), [](string &s1, string &s2) { return s1 + s2; });
    auto p2 = std::accumulate(word2.begin(), word2.end(), string(""), [](string &s1, string &s2) { return s1 + s2; });
    string p3;
    string p4;
    std::for_each(word1.begin(), word1.end(), [&](const string &s) { p3 += s; });
    std::for_each(word2.begin(), word2.end(), [&](const string &s) { p4 += s; });
    return p1 == p2 && p3 == p4;
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
  EXPECT_TRUE(s.arrayStringsAreEqual(n1, n2));
  EXPECT_FALSE(s.arrayStringsAreEqual(n3, n4));
  EXPECT_TRUE(s.arrayStringsAreEqual(n5, n6));
  EXPECT_SUMMARY;
}

int main()
{
  testArrayStringsAreEqual();
  return 0;
}
