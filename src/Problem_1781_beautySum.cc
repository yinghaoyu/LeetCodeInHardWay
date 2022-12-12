#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int beautySum(string s)
  {
    int n = s.length();
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
      int max = 0;
      int cnt[26] = {0};
      for (int j = i; j < n; j++)
      {
        // i...j的子串
        cnt[s[j] - 'a']++;
        // 预处理
        max = std::max(max, cnt[s[j] - 'a']);
        int min = n;
        for (int k = 0; k < 26; k++)
        {
          if (cnt[k] > 0)
          {
            // 美丽值是最大与最小字符频率之差，字符频率最小值不能为0
            min = std::min(min, cnt[k]);
          }
        }
        ans += max - min;
      }
    }
    return ans;
  }
};

void testBeautySum()
{
  Solution s;
  EXPECT_EQ_INT(5, s.beautySum("aabcb"));
  EXPECT_EQ_INT(17, s.beautySum("aabcbaa"));
  EXPECT_SUMMARY;
}

int main()
{
  testBeautySum();
  return 0;
}
