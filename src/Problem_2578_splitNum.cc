#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int splitNum(int num)
  {
    // 对于一个数 xxxx 最高位越小，最后的数才会越小，和也越小
    // 同时两个数的位数差不超过 1，证明见官解
    string str = to_string(num);
    std::sort(str.begin(), str.end());
    vector<int> x(2);
    for (int i = 0; i < str.length(); i++)
    {
      x[i & 1] = x[i & 1] * 10 + (str[i] - '0');
    }
    return x[0] + x[1];
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(59, s.splitNum(4325));
  EXPECT_EQ_INT(75, s.splitNum(687));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
