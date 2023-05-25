#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> getDiff(string &s)
  {
    int n = s.length();
    vector<int> diff(n - 1);
    for (int i = 0; i < n - 1; i++)
    {
      diff[i] = s[i + 1] - s[i];
    }
    return diff;
  }
  string oddString(vector<string> &words)
  {
    auto d0 = getDiff(words[0]);
    auto d1 = getDiff(words[1]);
    if (d0 == d1)
    {
      for (int i = 2; i < words.size(); i++)
      {
        if (d0 != getDiff(words[i]))
        {
          return words[i];
        }
      }
    }
    return d0 == getDiff(words[2]) ? words[1] : words[0];
  }
};

void testOddString()
{
  Solution s;
  vector<string> w1 = {"adc", "wzy", "abc"};
  vector<string> w2 = {"aaa", "bob", "ccc", "ddd"};
  EXPECT_TRUE("abc" == s.oddString(w1));
  EXPECT_TRUE("bob" == s.oddString(w2));
  EXPECT_SUMMARY;
}

int main()
{
  testOddString();
  return 0;
}
