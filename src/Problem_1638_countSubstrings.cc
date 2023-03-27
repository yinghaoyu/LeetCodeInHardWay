#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 暴力枚举
  int countSubstrings1(string s, string t)
  {
    int M = s.size();
    int N = t.size();
    int ans = 0;
    // 枚举起点
    for (int i = 0; i < M; i++)
    {
      for (int j = 0; j < N; j++)
      {
        int diff = 0;
        // 枚举长度
        for (int k = 0; i + k < M && j + k < N; k++)
        {
          diff += s[i + k] == t[j + k] ? 0 : 1;
          if (diff > 1)
          {
            break;
          }
          else if (diff == 1)
          {
            ans++;
          }
        }
      }
    }
    return ans;
  }

  int countSubstrings2(string s, string t)
  {
    int N = s.size(), M = t.size();
    // dpl[i][j]的含义为：必须以s[i]与t[j]为结尾，左侧连续相等的最大长度
    vector<vector<int>> dpl(N + 1, vector<int>(M + 1));
    // dpr[i][j]的含义为：必须以s[i]与t[j]为结尾，右侧连续相等的最大长度
    vector<vector<int>> dpr(N + 1, vector<int>(M + 1));
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        dpl[i + 1][j + 1] = s[i] == t[j] ? (dpl[i][j] + 1) : 0;
      }
    }
    for (int i = N - 1; i >= 0; i--)
    {
      for (int j = M - 1; j >= 0; j--)
      {
        dpr[i][j] = s[i] == t[j] ? (dpr[i + 1][j + 1] + 1) : 0;
      }
    }
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        if (s[i] != t[j])
        {
          // 左右两边都可以取空的情况，因此都需要+1
          // 然后进行排列组合
          ans += (dpl[i][j] + 1) * (dpr[i + 1][j + 1] + 1);
        }
      }
    }
    return ans;
  }
};

void testCountSubStrings()
{
  Solution s;
  EXPECT_EQ_INT(6, s.countSubstrings1("aba", "baba"));
  EXPECT_EQ_INT(3, s.countSubstrings1("ab", "bb"));
  EXPECT_SUMMARY;
}

int main()
{
  testCountSubStrings();
  return 0;
}
