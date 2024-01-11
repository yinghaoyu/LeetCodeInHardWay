#include <algorithm>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findTheLongestSubstring(string s)
  {
    int n = s.length();
    // 只有5个元音字符，状态就5位
    vector<int> map(32);
    // map[0...31] = -2
    // map[01100] = -2, 这个状态之前没出现过
    std::fill(map.begin(), map.end(), -2);
    map[0] = -1;
    int ans = 0;
    for (int i = 0, status = 0, m; i < n; i++)
    {
      // status : 0....i-1字符串上，aeiou的奇偶性
      // s[i] = 当前字符
      // 情况1 : 当前字符不是元音，status不变
      // 情况2 : 当前字符是元音，a~u(0~4)，修改相应的状态
      m = move(s[i]);
      if (m != -1)
      {
        status ^= (1 << m);
      }
      // status:  0....i字符串上，aeiou的奇偶性
      // 同样的状态，之前最早出现在哪
      if (map[status] != -2)
      {
        ans = std::max(ans, i - map[status]);
      }
      else
      {
        map[status] = i;
      }
    }
    return ans;
  }

  int move(char c)
  {
    switch (c)
    {
    case 'a':
      return 0;
    case 'e':
      return 1;
    case 'i':
      return 2;
    case 'o':
      return 3;
    case 'u':
      return 4;
    default:
      return -1;
    }
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(13, s.findTheLongestSubstring("eleetminicoworoep"));
  EXPECT_EQ_INT(5, s.findTheLongestSubstring("leetcodeisgreat"));
  EXPECT_EQ_INT(6, s.findTheLongestSubstring("bcbcbc"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
