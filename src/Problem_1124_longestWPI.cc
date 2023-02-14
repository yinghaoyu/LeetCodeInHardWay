#include <iostream>
#include <stack>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int longestWPI(vector<int> &hours)
  {
    int n = hours.size();
    vector<int> s(n + 1);
    stack<int> stk;
    stk.push(0);
    for (int i = 1; i <= n; i++)
    {
      s[i] = s[i - 1] + (hours[i - 1] > 8 ? 1 : -1);
      if (s[stk.top()] > s[i])
      {
        stk.push(i);
      }
    }

    int ans = 0;
    for (int r = n; r >= 1; r--)
    {
      while (stk.size() && s[stk.top()] < s[r])
      {
        ans = std::max(ans, r - stk.top());
        stk.pop();
      }
    }
    return ans;
  }
};

void testLongestWPI()
{
  Solution s;
  vector<int> h1 = {9, 9, 6, 0, 6, 6, 9};
  vector<int> h2 = {6, 6, 6};
  vector<int> h3 = {6, 6, 9};
  vector<int> h4 = {6, 9, 6};
  EXPECT_EQ_INT(3, s.longestWPI(h1));
  EXPECT_EQ_INT(0, s.longestWPI(h2));
  EXPECT_EQ_INT(1, s.longestWPI(h3));
  EXPECT_EQ_INT(1, s.longestWPI(h4));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestWPI();
  return 0;
}
