#include <functional>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  vector<string> removeInvalidParentheses(string s)
  {
    // 得到左右括号抵消后，需要删除的数量
    int left = 0;
    int right = 0;
    for (char c : s)
    {
      if (c == '(')
      {
        left++;
      }
      else if (c == ')')
      {
        if (left == 0)
        {
          right++;
        }
        else
        {
          left--;
        }
      }
    }

    vector<string> ans;
    f(s, 0, left, right, ans);
    return ans;
  }

  void f(string str, int index, int left, int right, vector<string>& ans)
  {
    if (left == 0 && right == 0)
    {
      if (isValid(str))
      {
        ans.push_back(str);
      }
      return;
    }
    for (int i = index; i < str.size(); i++)
    {
      if (i != index && str[i] == str[i - 1])
      {
        // 剪枝，一段连续的字符删除任意一个效果是一样的
        continue;
      }

      if (left + right > str.size() - i)
      {
        // 如果剩余的字符无法满足去掉的数量要求，直接返回
        return;
      }
      if (left > 0 && str[i] == '(')
      {
        // 尝试去掉一个左括号
        f(str.substr(0, i) + str.substr(i + 1), i, left - 1, right, ans);
      }
      if (right > 0 && str[i] == ')')
      {
        f(str.substr(0, i) + str.substr(i + 1), i, left, right - 1, ans);
      }
    }
  }

  bool isValid(string& str)
  {
    int cnt = 0;
    for (int i = 0; i < str.length(); i++)
    {
      if (str[i] == '(')
      {
        cnt++;
      }
      else if (str[i] == ')')
      {
        if (--cnt < 0)
        {
          return false;
        }
      }
    }
    return cnt == 0;
  }
};
