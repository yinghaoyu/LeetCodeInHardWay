#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int countUnique(string &s)
  {
    int ans = 0;
    int book[256] = {0};
    for (int i = 0; i < s.length(); i++)
    {
      book[s[i]]++;
    }
    for (int i = 0; i < s.length(); i++)
    {
      if (book[s[i]] == 1)
      {
        ans++;
      }
    }
    return ans;
  }

  int process(string s)
  {
    int ans = 0;
    vector<string> strs;
    for (int i = 0; i < s.length(); i++)
    {
      for (int j = i; j < s.length(); j++)
      {
        strs.push_back(s.substr(i, j - i + 1));
      }
    }
    for (string str : strs)
    {
      ans += countUnique(str);
    }
    return ans;
  }

  int uniqueLetterString(string s)
  {
    int N = s.length();
    int ans = 0;
    vector<int> left(N);
    vector<int> right(N);
    int cnts[26];  // cnts[26] = {-1}; 只会将第一个元素置位-1
    std::fill_n(cnts, 26, -1);
    for (int i = 0; i < N; i++)
    {
      int u = s[i] - 'A';
      left[i] = cnts[u];
      cnts[u] = i;
    }
    std::fill_n(cnts, 26, N);
    for (int i = N - 1; i >= 0; i--)
    {
      int u = s[i] - 'A';
      right[i] = cnts[u];
      cnts[u] = i;
    }
    for (int i = 0; i < N; i++)
    {
      ans += (i - left[i]) * (right[i] - i);
    }
    return ans;
  }
};

void testUniqueLetterString()
{
  Solution s;
  string s1 = "ABC";
  string s2 = "ABA";
  string s3 = "LEETCODE";
  EXPECT_EQ_INT(10, s.process(s1));
  EXPECT_EQ_INT(8, s.process(s2));
  EXPECT_EQ_INT(92, s.process(s3));
  EXPECT_EQ_INT(s.process(s1), s.uniqueLetterString(s1));
  EXPECT_EQ_INT(s.process(s2), s.uniqueLetterString(s2));
  EXPECT_EQ_INT(s.process(s3), s.uniqueLetterString(s3));
  EXPECT_SUMMARY;
}

int main()
{
  testUniqueLetterString();
  return 0;
}
