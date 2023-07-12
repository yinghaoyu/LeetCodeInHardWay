#include <vector>
#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
      // idx[s[i]] 表示 s[i] 字符最后出现的位置
      vector<int> idx(256, -1);
      int ans = 0;
      // pre 表示字符最后出现的位置
      int pre = -1;
      for(int i = 0; i < s.length(); i++)
      {
        // 第 1 次出现保存在 idx[s[i]]
        // pre 往后移动
        // 第 2 次出现用 i - pre
        pre = std::max(pre, idx[s[i]]);
        int cur = i - pre;
        ans = std::max(ans, cur);
        idx[s[i]] = i;
      }
      return ans;
    }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(3, s.lengthOfLongestSubstring("abcabcbb"));
  EXPECT_EQ_INT(1, s.lengthOfLongestSubstring("bbbbb"));
  EXPECT_EQ_INT(3, s.lengthOfLongestSubstring("pwwkew"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
    return 0;
}
