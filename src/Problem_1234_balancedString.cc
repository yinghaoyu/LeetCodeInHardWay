#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int idx(const char &c) { return c - 'A'; }

  int balancedString(string s)
  {
    vector<int> cnt(26);
    for (auto c : s)
    {
      // 统计每种字符出现的次数
      cnt[idx(c)]++;
    }

    int partial = s.length() / 4;
    auto check = [&]() {
      if (cnt[idx('Q')] > partial || cnt[idx('W')] > partial || cnt[idx('E')] > partial || cnt[idx('R')] > partial)
      {
        // not balanced
        return false;
      }
      // balanced
      return true;
    };

    if (check())
    {
      return 0;
    }
    int ans = s.length();
    // 替换子串的窗口
    for (int l = 0, r = 0; l < s.length(); l++)
    {
      while (r < s.length() && !check())
      {
        // 扩大窗口时，原串s对应的字符数减少
        cnt[idx(s[r])]--;
        r++;
      }
      if (!check())
      {
        // r == s.length()时，s任然存在字符数量 > avg
        // 后续缩小子串窗口，s串的字符数增大，这并不能减少s某些的字符数量
        // 因此后续尝试缩小子串窗口无意思
        break;
      }
      // 尝试缩小子串窗口
      ans = std::min(ans, r - l);
      cnt[idx(s[l])]++;
    }
    return ans;
  }
};

void testBalancedString()
{
  Solution s;
  EXPECT_EQ_INT(0, s.balancedString("QWER"));
  EXPECT_EQ_INT(1, s.balancedString("QQWE"));
  EXPECT_EQ_INT(2, s.balancedString("QQQW"));
  EXPECT_SUMMARY;
}

int main()
{
  testBalancedString();
  return 0;
}
