#include <string>
#include <utility>

using namespace std;

class Solution
{
 public:
  string reverseWords(string s)
  {
    int n = s.length();
    int i = 0;
    while (i < n)
    {
      // 找到单词
      int l = i;
      while (i < n && s[i] != ' ')
      {
        i++;
      }
      // 翻转字符串
      int r = i - 1;
      while (l < r)
      {
        std::swap(s[l++], s[r--]);
      }
      // 跳过空格
      while (i < n && s[i] == ' ')
      {
        i++;
      }
    }
    return s;
  }
};
