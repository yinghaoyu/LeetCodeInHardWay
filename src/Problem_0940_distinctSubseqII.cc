#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递推关系：
  // 例如 str = aba
  // 空集: {}
  // 加入a: {} {a}  ---> 保留空集，纯新增{a}
  // 加入b: {} {a} {b} {ab} --> 保留{} {a}，纯新增 {b} {ab}
  // 加入a: {} {a} {b} {ab} {a} {aa} {ba} {aba}，这时需要去重 {a}，发现刚好减去前一次加入a的纯新增
  int distinctSubseqII(string str)
  {
    if (str.length() == 0)
    {
      return 0;
    }
    int m = 1000000007;
    vector<int> count(26);
    int all = 1;
    for (char x : str)
    {
      // 纯新增 = 上次的基础 - 去重
      int newAdd = (all - count[x - 'a'] + m) % m;
      // 当前 = 保留上次 + 纯新增
      all = (all + newAdd) % m;
      count[x - 'a'] = (count[x - 'a'] + newAdd) % m;
    }
    return (all - 1 + m) % m;
  }
};

void testDistinctSubseqII()
{
  Solution s;
  EXPECT_EQ_INT(7, s.distinctSubseqII("abc"));
  EXPECT_EQ_INT(6, s.distinctSubseqII("aba"));
  EXPECT_EQ_INT(3, s.distinctSubseqII("aaa"));
  EXPECT_SUMMARY;
}

int main()
{
  testDistinctSubseqII();
  return 0;
}
