#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string mergeAlternately(string word1, string word2)
  {
    int n = word1.length();
    int m = word2.length();
    int i = 0;
    int j = 0;
    int idx = 0;
    string ans(m + n, '0');
    while (i < n && j < m)
    {
      if (idx & 1)
      {
        ans[idx++] = word2[j++];
      }
      else
      {
        ans[idx++] = word1[i++];
      }
    }
    while (i < n)
    {
      ans[idx++] = word1[i++];
    }
    while (j < m)
    {
      ans[idx++] = word2[j++];
    }
    return ans;
  }
};

bool isSameString(string a, string b)
{
  return a == b;
}

void testMergeAlternately()
{
  Solution s;
  EXPECT_TRUE(isSameString("apbqcr", s.mergeAlternately("abc", "pqr")));
  EXPECT_TRUE(isSameString("apbqrs", s.mergeAlternately("ab", "pqrs")));
  EXPECT_TRUE(isSameString("apbqcd", s.mergeAlternately("abcd", "pq")));
  EXPECT_SUMMARY;
}

int main()
{
  testMergeAlternately();
  return 0;
}
