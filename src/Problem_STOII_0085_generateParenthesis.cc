#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/generate-parentheses/
// @sa Problem_0022_generateParenthesis.cc

class Solution
{
 public:
  void process(int index, int rest, int gap, string &path, vector<string> &ans)
  {
    if (index == path.size())
    {
      ans.push_back(path);
      return;
    }
    if (rest > 0)
    {
      path[index] = '(';
      process(index + 1, rest - 1, gap + 1, path, ans);
    }
    if (gap > 0)
    {
      path[index] = ')';
      process(index + 1, rest, gap - 1, path, ans);
    }
  }

  vector<string> generateParenthesis(int n)
  {
    string path(n << 1, ' ');
    vector<string> ans;
    process(0, n, 0, path, ans);
    return ans;
  }
};
