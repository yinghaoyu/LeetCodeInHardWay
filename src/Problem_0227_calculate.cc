#include <deque>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int calculate(string s)
  {
    deque<string> st;
    string digit;
    for (int i = 0; i < s.length(); i++)
    {
      if (s[i] != ' ')
      {
        if (s[i] >= '0' && s[i] <= '9')
        {
          digit.push_back(s[i]);
        }
        else
        {
          handleStack(st, digit, s[i]);
          digit.clear();
        }
      }
    }
    handleStack(st, digit, ' ');
    // 最后计算加减法
    return computeStack(st);
  }

  void handleStack(deque<string> &st, string digit, char op)
  {
    if (st.empty() || st.back() == "+" || st.back() == "-")
    {
      // 先不计算加减法，全部入栈
      st.push_back(digit);
    }
    else
    {
      // 计算乘除法
      int num = stoi(digit);
      string preOp = st.back();
      st.pop_back();
      int preNum = stoi(st.back());
      st.pop_back();
      if (preOp == "*")
      {
        st.push_back(std::to_string(preNum * num));
      }
      else
      {
        st.push_back(std::to_string(preNum / num));
      }
    }
    st.push_back(string(1, op));
  }

  int computeStack(deque<string> &st)
  {
    int ans = stoi(st.front());
    st.pop_front();
    while (st.size() != 1)
    {
      string op = st.front();
      st.pop_front();
      int cur = stoi(st.front());
      st.pop_front();
      if (op == "+")
      {
        ans += cur;
      }
      else
      {
        ans -= cur;
      }
    }
    return ans;
  }
};

void testCalculate()
{
  Solution s;
  EXPECT_EQ_INT(7, s.calculate("3+2*2"));
  EXPECT_EQ_INT(1, s.calculate("3/2"));
  EXPECT_EQ_INT(5, s.calculate("3+5/2"));
  EXPECT_SUMMARY;
}

int main()
{
  testCalculate();
  return 0;
}
