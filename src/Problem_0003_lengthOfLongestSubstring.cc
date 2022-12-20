#include <iostream>
#include <numeric>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      if(s.length() == 0)
      {
        return 0;
      }
      int idx[256] = {0};
      for(int i = 0; i < 256; i++)
      {
        // idx的含义是，字符i最后出现的位置
        idx[i] = -1;
      }
      int len = 0;
      int pre = -1;
      int cur = 0;
      for(int i = 0; i < s.length(); i++)
      {
        // pre的含义是当前字符s[i]上一次出现的位置
        pre = std::max(pre, idx[s[i]]);
        cur = i - pre;
        len = std::max(len ,cur);
        idx[s[i]] = i;
      }
      return len;
    }
};

void testLengthOfLongestSubstring()
{
  Solution s;
  EXPECT_EQ_INT(3, s.lengthOfLongestSubstring("abcabcbb"));
  EXPECT_EQ_INT(1, s.lengthOfLongestSubstring("bbbbb"));
  EXPECT_EQ_INT(3, s.lengthOfLongestSubstring("pwwkew"));
  EXPECT_SUMMARY;
}

int main()
{
  testLengthOfLongestSubstring();
  return 0;
}
