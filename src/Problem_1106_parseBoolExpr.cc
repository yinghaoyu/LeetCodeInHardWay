#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool parseBoolExpr(string expression)
  {
    int n = expression.length();
    vector<char> stack;
    for (int i = 0; i < n; i++)
    {
      char c = expression[i];
      if (c == ',')
      {
        continue;
      }
      else if (c != ')')
      {
        stack.push_back(c);
      }
      else
      {
        int t = 0;
        int f = 0;
        while (stack.back() != '(')
        {
          char cur = stack.back();
          stack.pop_back();
          if (cur == 't')
          {
            t++;
          }
          else
          {
            f++;
          }
        }
        stack.pop_back();
        char op = stack.back();
        stack.pop_back();
        switch (op)
        {
        case '!':
        {
          stack.push_back(f == 1 ? 't' : 'f');
          break;
        }
        case '&':
        {
          stack.push_back(f == 0 ? 't' : 'f');
          break;
        }
        case '|':
        {
          stack.push_back(t > 0 ? 't' : 'f');
          break;
        }
        default:
        {
          break;
        }
        }
      }
    }
    return stack.back() == 't';
  }
};

void testParseBoolExpr()
{
  Solution s;
  EXPECT_FALSE(s.parseBoolExpr("&(|(f))"));
  EXPECT_TRUE(s.parseBoolExpr("|(f,f,f,t)"));
  EXPECT_TRUE(s.parseBoolExpr("!(&(f,t))"));
  EXPECT_SUMMARY;
}

int main()
{
  testParseBoolExpr();
  return 0;
}
