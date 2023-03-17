#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestValidParentheses(string s)
  {
    if (s.length() == 0)
    {
      return 0;
    }
    int N = s.length();
    vector<int> dp(N);
    int pre = 0;
    int ans = 0;
    for (int i = 1; i < N; i++)
    {
      if (s[i] == ')')
      {
        // pre是当前i位置的)，应该找哪个位置的(
        pre = i - dp[i - 1] - 1;
        if (pre >= 0 && s[pre] == '(')
        {
          dp[i] = dp[i - 1] + 2 + (pre > 0 ? dp[pre - 1] : 0);
        }
      }
      ans = std::max(ans, dp[i]);
    }
    return ans;
  }
};

void testLongestValidParentheses()
{
  Solution s;
  EXPECT_EQ_INT(2, s.longestValidParentheses("(()"));
  EXPECT_EQ_INT(4, s.longestValidParentheses(")()())"));
  EXPECT_EQ_INT(0, s.longestValidParentheses(""));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestValidParentheses();
  return 0;
}
