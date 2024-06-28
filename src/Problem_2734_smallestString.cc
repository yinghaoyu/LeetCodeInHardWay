#include <string>

using namespace std;

class Solution
{
 public:
  string smallestString(string s)
  {
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (s[i] > 'a')
      {
        // 把第一个不是a的字符，到第一个是a字符前之间的字符，全部替换
        for (; i < n && s[i] > 'a'; i++)
        {
          s[i]--;
        }
        return s;
      }
    }
    // 所有字符均为a
    s.back() = 'z';
    return s;
  }
};
