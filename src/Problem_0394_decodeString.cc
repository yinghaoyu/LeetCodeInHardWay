#include <cctype>
#include <iostream>
#include <tuple>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // s[i....]  何时停？遇到   ']'  或者遇到 s的终止位置，停止
  std::tuple<string, int> process(string &s, int i)
  {
    int N = s.length();
    int times = 0;
    string str;
    while (i < N && s[i] != ']')
    {
      if (isdigit(s[i]))
      {
        times = times * 10 + s[i++] - '0';
      }
      else if (isalpha(s[i]))
      {
        str.push_back(s[i++]);
      }
      else
      {
        // s[i] == '['
        auto [next, end] = process(s, i + 1);
        str.append(timesString(times, next));
        i = end + 1;
        times = 0;
      }
    }
    return {str, i};
  }

  string timesString(int times, string str)
  {
    string ans;
    for (int i = 0; i < times; i++)
    {
      ans.append(str);
    }
    return ans;
  }

  string decodeString(string s) { return std::get<0>(process(s, 0)); }
};

void testDecodeString()
{
  Solution s;
  EXPECT_TRUE("aaabcbc" == s.decodeString("3[a]2[bc]"));
  EXPECT_TRUE("accaccacc" == s.decodeString("3[a2[c]]"));
  EXPECT_TRUE("abcabccdcdcdef" == s.decodeString("2[abc]3[cd]ef"));
  EXPECT_SUMMARY;
}

int main()
{
  testDecodeString();
  return 0;
}
