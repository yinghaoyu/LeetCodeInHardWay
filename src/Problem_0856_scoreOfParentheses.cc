#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 时间复杂度O(n^2)，空间复杂度O(n^2)
  int scoreOfParentheses1(string s)
  {
    if (s.length() == 2)
    {
      return 1;
    }
    int balance = 0;
    int len = 0;
    int N = s.length();
    for (int i = 0; i < N; i++)
    {
      // 找到平衡串区间
      balance += (s[i] == '(' ? 1 : -1);
      if (balance == 0)
      {
        len = i + 1;
        break;
      }
    }
    if (len == N)
    {
      return 2 * scoreOfParentheses1(s.substr(1, N - 2));
    }
    else
    {
      return scoreOfParentheses1(s.substr(0, len)) + scoreOfParentheses1(s.substr(len, N - len));
    }
  }

  // 时间复杂度O(n)，空间复杂度O(n)
  int scoreOfParentheses2(string s)
  {
    vector<int> st;
    st.push_back(0);
    for (auto c : s)
    {
      if (c == '(')
      {
        st.push_back(0);
      }
      else
      {
        int v = st.back();
        st.pop_back();
        st.back() += std::max(2 * v, 1);
      }
    }
    return st.back();
  }

  // 时间复杂度O(n)，空间复杂度O(1)
  int scoreOfParentheses3(string s)
  {
    int depth = 0, n = s.size(), score = 0;
    for (int i = 0; i < n; i++)
    {
      depth += (s[i] == '(' ? 1 : -1);
      if (s[i] == ')' && s[i - 1] == '(')
      {
        score += 1 << depth;
      }
    }
    return score;
  }
};

void testScoreOfParentheses()
{
  Solution s;

  EXPECT_EQ_INT(1, s.scoreOfParentheses1("()"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses1("(())"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses1("()()"));
  EXPECT_EQ_INT(1, s.scoreOfParentheses2("()"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses2("(())"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses2("()()"));
  EXPECT_EQ_INT(1, s.scoreOfParentheses3("()"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses3("(())"));
  EXPECT_EQ_INT(2, s.scoreOfParentheses3("()()"));
  EXPECT_SUMMARY;
}

int main()
{
  testScoreOfParentheses();
  return 0;
}
