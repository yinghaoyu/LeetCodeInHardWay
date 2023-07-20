#include <cctype>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// seem as leetcode 0150
// https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/
// see at Problem_0150_evalRPN.cc
class Solution
{
 public:
  bool isNumber(string &token) { return token != "+" && token != "-" && token != "*" && token != "/"; }

  int evalRPN(vector<string> &tokens)
  {
    vector<int> stack;
    int n = tokens.size();
    for (int i = 0; i < n; i++)
    {
      string &token = tokens[i];
      if (isNumber(token))
      {
        stack.push_back(stoi(token));
      }
      else
      {
        int num2 = stack.back();
        stack.pop_back();
        int num1 = stack.back();
        stack.pop_back();
        switch (token[0])
        {
        case '+':
          stack.push_back(num1 + num2);
          break;
        case '-':
          stack.push_back(num1 - num2);
          break;
        case '*':
          stack.push_back(num1 * num2);
          break;
        case '/':
          stack.push_back(num1 / num2);
          break;
        }
      }
    }
    return stack.back();
  }
};
