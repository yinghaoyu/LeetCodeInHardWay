#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int evalRPN(vector<string> &tokens)
  {
    vector<int> st;
    std::function<int(int, int, const string &)> compute = [](int a, int b, const string &cur) -> int
    {
      if (cur == "+")
      {
        return a + b;
      }
      else if (cur == "-")
      {
        return a - b;
      }
      else if (cur == "*")
      {
        return a * b;
      }
      else
      {
        return a / b;
      }
    };

    int n = tokens.size();
    for (int i = 0; i < n; i++)
    {
      string cur = tokens[i];
      if (cur == "+" || cur == "-" || cur == "*" || cur == "/")
      {
        int b = st.back();
        st.pop_back();
        int a = st.back();
        st.pop_back();
        st.push_back(compute(a, b, cur));
      }
      else
      {
        st.push_back(std::stoi(cur));
      }
    }
    return st[0];
  }
};

void testEvalRPN()
{
  Solution s;
  vector<string> t1 = {"2", "1", "+", "3", "*"};
  vector<string> t2 = {"4", "13", "5", "/", "+"};
  vector<string> t3 = {"10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"};
  EXPECT_EQ_INT(9, s.evalRPN(t1));
  EXPECT_EQ_INT(6, s.evalRPN(t2));
  EXPECT_EQ_INT(22, s.evalRPN(t3));
  EXPECT_SUMMARY;
}

int main()
{
  testEvalRPN();
  return 0;
}
