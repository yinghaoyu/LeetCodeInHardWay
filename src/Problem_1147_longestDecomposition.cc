#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/longest-chunked-palindrome-decomposition/solution/tu-jie-tan-xin-zuo-fa-yi-tu-miao-dong-py-huik/
class Solution
{
 public:
  // 递归
  int process(string str)
  {
    if (str.length() == 0)
    {
      return 0;
    }
    for (int i = 1, n = str.length(); i <= n / 2; i++)
    {
      if (str.substr(0, i) == str.substr(n - i))
      {
        return 2 + longestDecomposition1(str.substr(i, n - i * 2));
      }
    }
    return 1;
  }

  int longestDecomposition1(string text) { return process(text); }

  // 迭代
  int longestDecomposition2(string text)
  {
    int ans = 0;
    while (!text.empty())
    {
      int i = 1;
      int n = text.length();
      while (i <= n / 2 && text.substr(0, i) != text.substr(n - i))
      {
        i++;
      }
      if (i > n / 2)
      {
        ++ans;
        break;
      }
      ans += 2;
      text = text.substr(i, n - i * 2);
    }
    return ans;
  }
};

void testLongestDecomposition()
{
  Solution s;
  EXPECT_EQ_INT(7, s.longestDecomposition1("ghiabcdefhelloadamhelloabcdefghi"));
  EXPECT_EQ_INT(1, s.longestDecomposition1("merchant"));
  EXPECT_EQ_INT(11, s.longestDecomposition1("antaprezatepzapreanta"));
  EXPECT_EQ_INT(7, s.longestDecomposition2("ghiabcdefhelloadamhelloabcdefghi"));
  EXPECT_EQ_INT(1, s.longestDecomposition2("merchant"));
  EXPECT_EQ_INT(11, s.longestDecomposition2("antaprezatepzapreanta"));
  EXPECT_SUMMARY;
}

int main()
{
  testLongestDecomposition();
  return 0;
}
