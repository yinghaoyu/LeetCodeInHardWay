#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int calculate(string s) { return f(s, 0)[0]; }

  // 充分运用递归思想
  vector<int> f(string& str, int i)
  {
    deque<string> que;
    int cur = 0;
    vector<int> bra;
    while (i < str.length() && str[i] != ')')
    {
      if (str[i] == ' ')
      {
        i++;
        continue;
      }
      if (isdigit(str[i]))
      {
        // 统计数值
        cur = cur * 10 + str[i++] - '0';
      }
      else if (str[i] != '(')
      {
        // 遇到运算符
        // 把数值加入到队列里
        addNum(que, cur);
        que.push_back(string(1, str[i++]));
        cur = 0;
      }
      else
      {
        // 遇到i左括号了
        bra = f(str, i + 1);
        cur = bra[0];
        i = bra[1] + 1;
      }
    }
    addNum(que, cur);
    // str[i] == ')'
    return {getNum(que), i};
  }

  void addNum(deque<string> &que, int num)
  {
    if (!que.empty())
    {
      int cur = 0;
      string top = que.back();
      que.pop_back();
      if (top == "+" || top == "-")
      {
        // 加法、减法留到最后做
        que.push_back(top);
      }
      else
      {
        cur = std::stoi(que.back());
        que.pop_back();
        num = top == "*" ? (cur * num) : (cur / num);
      }
    }
    que.push_back(std::to_string(num));
  }

  // 从左到右计算 + -
  int getNum(deque<string> &que)
  {
    int res = 0;
    bool add = true;
    string cur;
    int num = 0;
    while (!que.empty())
    {
      cur = que.front();
      que.pop_front();
      if (cur == "+")
      {
        add = true;
      }
      else if (cur == "-")
      {
        add = false;
      }
      else
      {
        num = std::stoi(cur);
        res += add ? num : (-num);
      }
    }
    return res;
  }
};

void testCaculate()
{
  Solution s;
  EXPECT_EQ_INT(2, s.calculate("1+1"));
  EXPECT_EQ_INT(4, s.calculate("6-4/2"));
  EXPECT_EQ_INT(21, s.calculate("2*(5+5*2)/3+(6/2 + 8)"));
  EXPECT_SUMMARY;
}

int main()
{
  testCaculate();
  return 0;
}
