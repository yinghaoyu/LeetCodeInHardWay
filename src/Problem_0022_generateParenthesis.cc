#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  void process(int cur, int rest, int gap, string &path, vector<string> &ans)
  {
    if (cur == path.length())
    {
      ans.push_back(path);
      return;
    }
    if (gap > 0)
    {
      path[cur] = ')';
      process(cur + 1, rest, gap - 1, path, ans);
    }
    if (rest > 0)
    {
      path[cur] = '(';
      process(cur + 1, rest - 1, gap + 1, path, ans);
    }
  }

  vector<string> generateParenthesis(int n)
  {
    string str(n << 1, ' ');
    vector<string> ans;
    process(0, n, 0, str, ans);
    return ans;
  }
};

bool isVectorEuqal(vector<string> a, vector<string> b)
{
  return a == b;
}

void testGenerateParenthesis()
{
  Solution s;
  vector<string> n1 = {"()()()", "()(())", "(())()", "(()())", "((()))"};
  vector<string> n2 = {"()"};
  EXPECT_TRUE(isVectorEuqal(n1, s.generateParenthesis(3)));
  EXPECT_TRUE(isVectorEuqal(n2, s.generateParenthesis(1)));
  EXPECT_SUMMARY;
}

int main()
{
  testGenerateParenthesis();
  return 0;
}
