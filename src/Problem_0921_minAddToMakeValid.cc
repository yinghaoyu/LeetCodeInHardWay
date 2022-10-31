#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minAddToMakeValid(string s)
  {
    vector<char> stack;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (!stack.empty() && stack.back() == '(' && s[i] == ')')
      {
        stack.pop_back();
      }
      else
      {
        stack.push_back(s[i]);
      }
    }
    return stack.size();
  }
};

void testMinAddToMakeValid()
{
  Solution s;
  EXPECT_EQ_INT(1, s.minAddToMakeValid("())"));
  EXPECT_EQ_INT(3, s.minAddToMakeValid("((("));
  EXPECT_EQ_INT(1, s.minAddToMakeValid("((())"));
  EXPECT_EQ_INT(1, s.minAddToMakeValid("((((((((())))))))"));
  EXPECT_EQ_INT(1, s.minAddToMakeValid("()()()()(((())))()("));
  EXPECT_SUMMARY;
}

int main()
{
  testMinAddToMakeValid();
  return 0;
}
