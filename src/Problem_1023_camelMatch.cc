#include <pthread.h>
#include <cctype>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<bool> camelMatch(vector<string> &queries, string pattern)
  {
    int n = queries.size();
    int m = pattern.length();
    vector<bool> ans(n, true);
    for (int i = 0; i < n; i++)
    {
      int k = 0;
      for (auto &c : queries[i])
      {
        if (k < m && pattern[k] == c)
        {
          k++;
        }
        else if (isupper(c))
        {
          ans[i] = false;
          break;
        }
      }
      if (k < m)
      {
        ans[i] = false;
      }
    }
    return ans;
  }
};

void testCamelMatch()
{
  Solution s;
  vector<string> q1 = {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"};
  vector<bool> o1 = {true, false, true, true, false};

  vector<string> q2 = {"FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack"};
  vector<bool> o2 = {false, true, false, false, false};
  EXPECT_TRUE(o1 == s.camelMatch(q1, "FB"));
  EXPECT_TRUE(o2 == s.camelMatch(q2, "FoBaT"));
  EXPECT_SUMMARY;
}

int main()
{
  testCamelMatch();
  return 0;
}
