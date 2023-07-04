#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 异或前缀和统计区间内字符出现的奇偶次数
class Solution
{
 public:
  vector<bool> canMakePaliQueries(string s, vector<vector<int>> &queries)
  {
    int n = s.size();
    vector<int> count(n + 1);
    for (int i = 0; i < n; i++)
    {
      // 异或前缀和
      // 如果区间内字符出现偶数次，那么给 count 贡献 0
      count[i + 1] = count[i] ^ (1 << (s[i] - 'a'));
    }
    vector<bool> ans;
    for (auto &query : queries)
    {
      int l = query[0];
      int r = query[1];
      int k = query[2];
      int bits = 0;
      // 这个个区间有多少字符出现奇数次
      int x = count[r + 1] ^ count[l];
      while (x > 0)
      {
        x &= x - 1;
        bits++;
      }
      // 由于可以重排列，因此偶数字符放在左右两边
      // 奇数字符，由于可以替换 k 个， 最中间的 1 个奇数字符可以不替换
      // 所以只要满足奇数字符 bits <= k * 2 + 1 即可
      ans.push_back(bits <= k * 2 + 1);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> q1 = {{3, 3, 0}, {1, 2, 0}, {0, 3, 1}, {0, 3, 2}, {0, 4, 1}};
  vector<bool> o1 = {true, false, false, true, true};

  vector<vector<int>> q2 = {{0, 1, 0}, {2, 2, 1}};
  vector<bool> o2 = {false, true};

  EXPECT_TRUE(o1 == s.canMakePaliQueries("abcda", q1));
  EXPECT_TRUE(o2 == s.canMakePaliQueries("lyb", q2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
