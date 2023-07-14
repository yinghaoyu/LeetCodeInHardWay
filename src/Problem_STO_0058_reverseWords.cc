#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string reverseWords(string s)
  {
    if (s.empty())
    {
      return s;
    }
    string ans = "";
    int i = s.size() - 1;
    while (i >= 0)
    {
      while (i >= 0 && s[i] == ' ')
      {
        // 跳过空格
        --i;
      }
      int j = i;
      while (i >= 0 && s[i] != ' ')
      {
        --i;
      }
      if (i < j)
      {
        // 提取单词
        ans += s.substr(i + 1, j - i);
        ans += " ";
      }
    }
    return ans.substr(0, ans.size() - 1);
  }
};
