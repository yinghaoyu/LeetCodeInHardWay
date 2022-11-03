#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> getNextArray(string s)
  {
    int len = s.length();
    if (len == 1)  // KMP默认第一个next数组元素为-1
    {
      return {-1};
    }
    vector<int> next(len);
    next[0] = -1;
    next[1] = 0;
    int i = 2;   // 目前在哪个位置上求next数组的值
    int cn = 0;  // 当前是哪个位置的值再和i-1位置的字符比较
    while (i < len)
    {
      if (s[i - 1] == s[cn])
      {
        // 配成功的时候
        next[i++] = ++cn;
      }
      else if (cn > 0)
      {
        cn = next[cn];
      }
      else
      {
        next[i++] = 0;
      }
    }
    return next;
  }

  // 返回s2在s1的下标
  int getIndexOf(string s1, string s2)
  {
    if (s2 == "" || s2.length() < 1)
    {
      return 0;  // c++ 找空串默认找到下标为0
    }
    if (s1.length() < s2.length())
    {
      return -1;
    }
    int x = 0;
    int y = 0;
    // O(M) m <= n
    vector<int> next = getNextArray(s2);
    // O(N)
    while (x < s1.length() && y < s2.length())
    {
      if (s1[x] == s2[y])
      {
        x++;
        y++;
      }
      else if (next[y] == -1)
      {
        // y == 0
        x++;
      }
      else
      {
        y = next[y];
      }
    }
    return y == s2.length() ? x - y : -1;  // string::npos == -1
  }

  int maxRepeating1(string sequence, string word)
  {
    int ans = 0;
    string s = word;
    while (getIndexOf(sequence, s) != -1)
    {
      ans++;
      s += word;
    }
    return ans;
  }

  int maxRepeating2(string sequence, string word)
  {
    int n = sequence.size();
    int m = word.size();
    if (n < m)
    {
      return 0;
    }
    // dp[i]表示sequence[i]结尾的字符串，最大能构成多长的word重复子序列
    vector<int> dp(n);
    // 下标从m-1开始，保证前面至少有m个字符
    for (int i = m - 1; i < n; i++)
    {
      bool vaild = true;
      for (int j = 0; j < m; j++)  // 检查m长度内是否与word相等
      {
        if (sequence[i - m + j + 1] != word[j])
        {
          vaild = false;
          break;
        }
      }
      if (vaild)
      {
        // sequence[i-m+1 .. i]字符与word相等
        dp[i] = (i == m - 1 ? 0 : dp[i - m]) + 1;
      }
    }
    return *max_element(dp.begin(), dp.end());
  }
};

void testMaxRepeating()
{
  Solution s;
  EXPECT_EQ_INT(2, s.maxRepeating1("ababc", "ab"));
  EXPECT_EQ_INT(1, s.maxRepeating1("ababc", "ba"));
  EXPECT_EQ_INT(0, s.maxRepeating1("ababc", "ac"));
  EXPECT_EQ_INT(2, s.maxRepeating2("ababc", "ab"));
  EXPECT_EQ_INT(1, s.maxRepeating2("ababc", "ba"));
  EXPECT_EQ_INT(0, s.maxRepeating2("ababc", "ac"));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxRepeating();
  return 0;
}
