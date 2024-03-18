#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  void f(int index, int l, int r, string& path, vector<string>& ans)
  {
    if (index == path.length())
    {
      ans.push_back(path);
      return;
    }
    if (l > 0)
    {
      path[index] = '(';
      // 只有先填了左括号，才能填右括号
      f(index + 1, l - 1, r + 1, path, ans);
    }
    if (r > 0)
    {
      path[index] = ')';
      f(index + 1, l, r - 1, path, ans);
    }
  }

  vector<string> generateParenthesis(int n)
  {
    vector<string> ans;
    // 结果长度是可以确定的
    string path(n << 1, ' ');
    f(0, n, 0, path, ans);
    return ans;
  }
};
