#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxProduct(vector<string> &words)
  {
    unordered_map<int, int> map;
    for (auto &word : words)
    {
      // 位运算优化
      int mask = 0;
      int n = word.length();
      for (auto &c : word)
      {
        mask |= (1 << (c - 'a'));
      }
      if (map.count(mask))
      {
        if (n > map[mask])
        {
          map[mask] = n;
        }
      }
      else
      {
        map[mask] = n;
      }
    }
    int ans = 0;
    for (auto &[mask1, len1] : map)
    {
      for (auto &[mask2, len2] : map)
      {
        if ((mask1 & mask2) == 0)
        {
          ans = std::max(ans, len1 * len2);
        }
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<string> w1 = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  vector<string> w2 = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
  vector<string> w3 = {"a", "aa", "aaa", "aaaa"};
  EXPECT_EQ_INT(16, s.maxProduct(w1));
  EXPECT_EQ_INT(4, s.maxProduct(w2));
  EXPECT_EQ_INT(0, s.maxProduct(w3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
