#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int findSubstringInWraproundString(string s)
  {
    // cnt[c]的含义为：
    // 必须以c字符为结尾，符合条件的子串最大长度
    vector<int> cnt(256);
    int n = s.length();
    cnt[s[0]] = 1;
    // 前一个字符成长的长度
    int len = 1;
    for (int i = 1; i < n; i++)
    {
      char pre = s[i-1];
      char cur = s[i];
      if ((pre == 'z' && cur == 'a') || pre == cur - 1)
      {
        // 是连续的
        len++;
      }
      else
      {
        len = 1;
      }
      cnt[cur] = std::max(cnt[cur], len);
    }
    // 答案，s中有多少不同的非空子串，也是想象串的子串
    int ans = 0;
    for (int i = 0; i < 256; i++)
    {
      // 对于长度为4的子串 abcd，刚好有 4 个子串满足条件， a、ab、abc、abcd
      ans += cnt[i];
    }
    return ans;
  }
};

void testFindSubstringInWraproundString()
{
  Solution s;
  EXPECT_EQ_INT(1, s.findSubstringInWraproundString("a"));
  EXPECT_EQ_INT(2, s.findSubstringInWraproundString("cac"));
  EXPECT_EQ_INT(6, s.findSubstringInWraproundString("zab"));
  EXPECT_SUMMARY;
}

int main()
{
  testFindSubstringInWraproundString();
  return 0;
}
